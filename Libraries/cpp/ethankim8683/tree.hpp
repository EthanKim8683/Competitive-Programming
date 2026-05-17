#ifndef ETHANKIM8683_TREE
#define ETHANKIM8683_TREE 1

#include <algorithm>
#include <cassert>
#include <ctime>
#include <functional>
#include <random>
#include <vector>

namespace ethankim8683 {

// Euler tour and binary lifting-based tree utils
// TODO:
// - O(1) RMQ LCA (or see https://codeforces.com/blog/entry/153134)
// - O(1) kth ancestor (ladder)
// - Built-in HLD
struct tree_utils {
 private:
  const std::vector<std::vector<int>> &adj;
  int n, logn;
  int r;
  std::vector<int> in, out;
  std::vector<int> depth;
  std::vector<std::vector<int>> anc;

 public:
  tree_utils(const std::vector<std::vector<int>> &_adj, int _r = 0)
      : adj(_adj),
        n(adj.size()),
        logn(std::__lg(n) + 1),
        r(_r),
        in(n),
        out(n),
        depth(n),
        anc(n, std::vector<int>(logn)) {
    int t = 0;
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      in[a] = t++;
      anc[a][0] = p;
      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
      out[a] = t;
    };
    dfs(dfs, r, r, 0);

    for (int i = 1; i < logn; i++) {
      for (int j = 0; j < n; j++) {
        anc[j][i] = anc[anc[j][i - 1]][i - 1];
      }
    }
  }

  int get_index(int a) const { return in[a]; }
  std::pair<int, int> get_range(int a) const { return {in[a], out[a]}; }

  int get_depth(int a) const { return depth[a]; }

  int get_parent(int a) const {
    assert(a != r);
    return anc[a][0];
  }

  bool is_anc(int a, int b) const {
    return in[a] <= in[b] and out[a] >= out[b];
  }

  int lca(int a, int b) const {
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = logn - 1; i >= 0; i--) {
      if (!is_anc(anc[a][i], b)) {
        a = anc[a][i];
      }
    }
    return anc[a][0];
  }

  int dist(int a, int b) const {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
  }

  int kth_anc(int a, int k) const {
    assert(0 <= k and k <= depth[a]);
    for (int i = logn - 1; i >= 0; i--) {
      if (k >> i & 1) {
        a = anc[a][i];
      }
    }
    return a;
  }

  int kth_on_path(int a, int b, int k) const {
    assert(0 <= k and k <= dist(a, b));
    int c = lca(a, b);
    if (k <= dist(a, c)) {
      return kth_anc(a, k);
    } else {
      return kth_anc(b, dist(a, b) - k);
    }
  }

  bool is_on_path(int a, int b, int c) const {
    return is_anc(lca(a, b), c) and (is_anc(c, a) or is_anc(c, b));
  }

  bool is_in_subtree(int a, int b, int r) const { return is_on_path(r, b, a); }
  bool is_in_subtree(int a, int b) const { return is_in_subtree(a, b, r); }

  // https://www.youtube.com/watch?v=czySm7bUHgY
  // Returns the root and edges of a virtual tree containing the given vertices
  // O(V\log(V))
  std::pair<int, std::vector<std::pair<int, int>>> virtual_tree(
      std::vector<int> v) const {
    int k = v.size();
    assert(k > 0);

    auto cmp = [&](int a, int b) -> bool { return in[a] < in[b]; };
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i + 1 < k; i++) {
      v.push_back(lca(v[i], v[i + 1]));
    }
    sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());

    std::vector<int> stack;
    std::vector<std::pair<int, int>> rv;
    for (auto a : v) {
      while (stack.size() >= 2 and !is_anc(stack.back(), a)) {
        rv.push_back({stack.end()[-2], stack.back()});
        stack.pop_back();
      }
      stack.push_back(a);
    }
    while (stack.size() >= 2) {
      rv.push_back({stack.end()[-2], stack.back()});
      stack.pop_back();
    }
    return {stack[0], rv};
  }

  std::vector<int> subtree(int r) {
    std::vector<int> rv;
    auto dfs = [&](auto self, int a, int p) -> void {
      rv.push_back(a);
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    dfs(dfs, r, anc[r][0]);
    return rv;
  }
};

// https://codeforces.com/blog/entry/124286
// https://atcoder.jp/contests/abc351/editorial/9899
// pajenegod's re-root template, with AtCoder/Static Top Tree-inspired structure
// O(N)
template <class T, class S>
std::pair<std::vector<T>, std::vector<std::vector<T>>> rrdp(
    const std::function<S(T, int, int)> &transition,
    const std::function<S(S, S)> &combine,
    const std::function<T(S, int)> &finalize, S nil,
    const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<S> draft_dp(n);
  std::vector<std::vector<T>> adj_dp(n);
  auto dfs_up = [&](auto self, int a, int p = -1) -> T {
    adj_dp[a].resize(adj[a].size());
    draft_dp[a] = nil;

    for (int i = 0; i < adj[a].size(); i++) {
      int b = adj[a][i];
      if (b == p) continue;

      adj_dp[a][i] = self(self, b, a);
      draft_dp[a] = combine(draft_dp[a], transition(adj_dp[a][i], a, i));
    }

    return finalize(draft_dp[a], a);
  };
  dfs_up(dfs_up, 0);

  std::vector<T> dp(n);
  auto dfs_down = [&](auto self, int a, int p = -1) -> void {
    std::vector<S> prefix_dp(adj[a].size(), nil);
    for (int i = 0; i + 1 < adj[a].size(); i++) {
      prefix_dp[i + 1] = combine(prefix_dp[i], transition(adj_dp[a][i], a, i));
    }

    std::vector<S> suffix_dp(adj[a].size(), nil);
    for (int i = adj[a].size() - 1; i - 1 >= 0; i--) {
      suffix_dp[i - 1] = combine(transition(adj_dp[a][i], a, i), suffix_dp[i]);
    }

    for (int i = 0; i < adj[a].size(); i++) {
      int b = adj[a][i];
      if (b == p) continue;

      int j = std::find(adj[b].begin(), adj[b].end(), a) - adj[b].begin();
      adj_dp[b][j] = finalize(combine(prefix_dp[i], suffix_dp[i]), a);
      dp[b] = finalize(combine(draft_dp[b], transition(adj_dp[b][j], b, j)), b);

      self(self, b, a);
    }
  };
  dfs_down(dfs_down, 0);
  dp[0] = finalize(draft_dp[0], 0);

  return {dp, adj_dp};
}

// Returns all (one or two) centroids of the tree
// O(N)
std::vector<int> find_centroids(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<int> size(n);
  auto dfs_size = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      size[a] += self(self, b, a);
    }
    return size[a];
  };
  dfs_size(dfs_size, 0, -1);

  std::vector<int> rv;
  auto dfs_find = [&](auto self, int a, int p) -> void {
    for (auto b : adj[a]) {
      if (b == p) continue;
      if (size[b] * 2 > n) {
        return self(self, b, a);
      } else if (size[b] * 2 == n) {
        rv.push_back(b);
      }
    }
    rv.push_back(a);
  };
  dfs_find(dfs_find, 0, -1);
  return rv;
}

// Returns a rooted tree corresponding to the centroid decomposition
// O(N\log(N))
std::pair<int, std::vector<std::vector<int>>> centroid_decomp(
    const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> cut(n, false);
  std::vector<int> size(n);
  auto dfs_size = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      size[a] += self(self, b, a);
    }
    return size[a];
  };

  auto dfs_find = [&](auto self, int a, int p, int k) -> int {
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      if (size[b] * 2 > k) {
        return self(self, b, a, k);
      }
    }
    return a;
  };

  std::vector<std::vector<int>> adj2(n);
  auto dfs_build = [&](auto self, int a) -> int {
    a = dfs_find(dfs_find, a, -1, dfs_size(dfs_size, a, -1));
    cut[a] = true;
    for (auto b : adj[a]) {
      if (cut[b]) continue;
      adj2[a].push_back(self(self, b));
    }
    return a;
  };
  int r = dfs_build(dfs_build, 0);
  return {r, adj2};
}

// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
// Returns a hash of the unlabeled rooted tree
// O(N)
template <long long MOD = (1ll << 61) - 1>
long long tree_hash(const std::vector<std::vector<int>> &adj, int r) {
  int n = adj.size();

  std::vector<int> depth(n);
  auto dfs_depth = [&](auto self, int a, int p) -> void {
    depth[a] = 0;
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
      depth[a] = std::max(depth[a], depth[b] + 1);
    }
  };
  dfs_depth(dfs_depth, r, -1);

  static std::mt19937_64 rng(time(nullptr));
  static std::vector<long long> vars = {1};
  while ((int) vars.size() < depth[r] + 1) {
    vars.push_back(rng() % MOD);
  }

  auto dfs_hash = [&](auto self, int a, int p) -> long long {
    long long hash = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      hash = (__int128) hash * (vars[depth[a]] + self(self, b, a)) % MOD;
    }
    return hash;
  };
  return dfs_hash(dfs_hash, r, -1);
}

// Returns a hash of the unlabeled unrooted tree
// O(N)
template <long long MOD = (1ll << 61) - 1>
long long tree_hash(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  auto roots = find_centroids(adj);
  std::vector<long long> hashes;
  for (auto r : roots) {
    hashes.push_back(tree_hash<long long, MOD>(adj, r));
  }
  sort(hashes.begin(), hashes.end());

  static long long base = std::mt19937_64(time(nullptr))() % MOD;
  long long rv = 0;
  for (auto e : hashes) {
    rv = ((__int128) rv * base + e) % MOD;
  }
  return rv;
}

// https://cp-algorithms.com/graph/pruefer_code.html
// Returns the Prüfer code of a labelled tree
std::vector<int> prufer_code(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<int> parent(n, -1);
  auto dfs = [&](auto self, int a) -> void {
    for (auto b : adj[a]) {
      if (b == parent[a]) continue;
      self(self, b);
    }
  };
  dfs(dfs, n - 1);

  std::vector<int> degree(n, 0);
  for (int i = 0; i < n; i++) {
    degree[i] = adj[i].size();
  }

  int j = -1;
  for (int i = 0; i < n; i++) {
    if (degree[i] != 1) continue;
    j = i;
    break;
  }

  std::vector<int> rv;
  int a = j;
  for (int i = 0; i < n - 2; i++) {
    int p = parent[a];
    rv.push_back(p);

    degree[p]--;
    if (degree[p] == 1 and p < j) {
      a = p;
    } else {
      do {
        j++;
      } while (degree[j] != 1);
      a = j;
    }
  }
  return rv;
}

// Rearranges adjacency lists in-place such that for each node:
// - First element is heavy child if there are children
// - Last element is parent if included in adjacency list
void sort_hld(std::vector<std::vector<int>> &adj, int r = 0) {
  auto dfs = [&](auto self, int a, int p) -> int {
    int rv = 1, nmax = 0;
    for (int i = 0; i < (int) adj[a].size(); i++) {
      if (adj[a][i] == p) {
        std::swap(adj[a][i], adj[a].back());
      }

      if (adj[a][i] == p) continue;
      int n = self(self, adj[a][i], a);
      rv += n;

      if (i == 0) {
        nmax = n;
      } else {
        if (n > nmax) {
          std::swap(adj[a][0], adj[a][i]);
          nmax = n;
        }
      }
    }
    return rv;
  };
  dfs(dfs, r, -1);
}

// https://atcoder.jp/contests/abc454/editorial/19133
// Small-to-large merging using global data structure; relaxes data structure
// sparseness condition
// O(N\log(N))
void sack(const std::function<void(int)> &insert,
          const std::function<void()> &clear,
          const std::function<void(int)> &callback,
          std::vector<std::vector<int>> &adj, int r = 0) {
  int n = adj.size();

  sort_hld(adj, r);

  std::vector<int> order(n);
  int t = 0;
  auto dfs = [&](auto self, int a, int p) -> void {
    order[t] = a;
    t++;

    int l = t;
    for (int i = 1; i < (int) adj[a].size(); i++) {
      if (adj[a][i] == p) continue;
      self(self, adj[a][i], a);
      clear();
    }
    int r = t;

    if ((int) adj[a].size() > 0 and adj[a][0] != p) {
      self(self, adj[a][0], a);
      for (int i = l; i < r; i++) {
        insert(order[i]);
      }
    }
    insert(a);

    callback(a);
  };
  dfs(dfs, r, -1);
}

}  // namespace ethankim8683

#endif  // ETHANKIM8683_TREE
