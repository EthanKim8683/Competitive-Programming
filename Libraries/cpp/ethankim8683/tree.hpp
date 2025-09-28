#ifndef ETHANKIM8683_TREE
#define ETHANKIM8683_TREE 1

#include <assert.h>

#include <algorithm>
#include <functional>
#include <random>
#include <vector>

#include "ethankim8683/data_structures"
#include "ethankim8683/type_traits"

// Euler tour and binary lifting-based tree utils
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
  // Returns the edges of a virtual tree corresponding to the given vertices
  // O(V\log{V})
  std::vector<std::pair<int, int>> virtual_tree(std::vector<int> v) const {
    for (auto a : v) {
      assert(0 <= a and a < n);
    }

    int k = v.size();

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
    return rv;
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
template <typename T, typename S>
std::pair<std::vector<T>, std::vector<std::vector<T>>> rrdp(
    const std::vector<std::vector<int>> &adj, S nil,
    const std::function<S(T, int, int)> &transition,
    const std::function<S(S, S)> &combine,
    const std::function<T(S, int)> &finalize) {
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

// Returns a rooted tree corresponding to the Cartesian tree
// O(N)
template <typename T>
std::pair<int, std::vector<std::vector<int>>> cartesian_tree(
    const std::vector<T> &v,
    const std::function<bool(T, T)> &cmp = std::less<T>()) {
  int n = v.size();

  std::vector<int> domain(n);
  iota(domain.begin(), domain.end(), 0);
  sparse_table<int> st(domain, -1, [&](int a, int b) -> int {
    if (a == -1) return b;
    if (b == -1) return a;
    return v[a] == v[b] ? std::min(a, b) : cmp(v[a], v[b]) ? a : b;
  });

  std::vector<std::vector<int>> adj(n);
  auto dfs = [&](auto self, int l, int r) -> int {
    auto m = st.query(l, r);
    if (l < m) {
      adj[m].push_back(self(self, l, m));
    }
    if (m + 1 < r) {
      adj[m].push_back(self(self, m + 1, r));
    }
    return m;
  };
  int r = dfs(dfs, 0, n);
  return {r, adj};
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
// O(N\log{N})
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

  std::vector<std::vector<int>> adj_(n);
  auto dfs_build = [&](auto self, int a) -> int {
    a = dfs_find(dfs_find, a, -1, dfs_size(dfs_size, a, -1));
    cut[a] = true;
    for (auto b : adj[a]) {
      if (cut[b]) continue;
      adj_[a].push_back(self(self, b));
    }
    return a;
  };
  int r = dfs_build(dfs_build, 0);
  return {r, adj_};
}

// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
// Returns a hash of the unlabeled rooted tree
// O(N)
template <typename T = long long, T MOD = (1ll << 61) - 1,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
T tree_hash(const std::vector<std::vector<int>> &adj, int r) {
  using T2 = double_width<T>::type;

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
  static std::vector<T> vars = {1};
  while (vars.size() < depth[r] + 1) {
    vars.push_back(rng() % MOD);
  }

  auto dfs_hash = [&](auto self, int a, int p) -> T {
    T hash = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      hash = (T2) hash * (vars[depth[a]] + self(self, b, a)) % MOD;
    }
    return hash;
  };
  return dfs_hash(dfs_hash, r, -1);
}

// Returns a hash of the unlabeled unrooted tree
// O(N)
template <typename T = long long, T MOD = (1ll << 61) - 1,
          std::enable_if<std::is_integral<T>::value>::type * = nullptr>
T tree_hash(const std::vector<std::vector<int>> &adj) {
  using T2 = double_width<T>::type;

  int n = adj.size();

  static T base = std::mt19937_64(time(nullptr))() % MOD;
  auto roots = find_centroids(adj);
  T rv = 0;
  for (auto r : roots) {
    rv = ((T2) rv * base + tree_hash<T, MOD>(adj, r)) % MOD;
  }
  return rv;
}

#endif  // ETHANKIM8683_TREE
