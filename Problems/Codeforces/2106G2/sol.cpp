#include <bits/stdc++.h>

#include "ethankim8683/tree"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

#ifdef ETHANKIM8683
    int R;
    cin >> R;
    R--;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
#endif

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    // find root in <= 200 operations
    //
    // binary searching for subtree for each centroid: O(log2(N) * log2(N))
    //
    // parity(sum' - sum - k) = {
    //   odd   if root's subtree root in U
    //   even  if root's subtree root not in U
    // }
    //
    // 1. get sum
    // 2. toggle centroid
    // 3. get sum'
    //
    // we don't want it to be odd, so we shrink it until it's even
    // if it's in the centroid, it will always be odd

    int Q = 0;

    auto query1 = [&](vector<int> U) -> int {
      Q++;
#ifdef ETHANKIM8683
      vector<int> sums(N, 0);
      auto dfs = [&](auto self, int a, int p) -> void {
        sums[a] += A[a];
        for (auto b : adj[a]) {
          if (b == p) continue;
          sums[b] = sums[a];
          self(self, b, a);
        }
      };
      dfs(dfs, R, -1);

      int rv = 0;
      for (auto e : U) {
        rv += sums[e];
      }
      return rv;
#else
      cout << "? 1 " << U.size();
      for (auto u : U) {
        cout << ' ' << u + 1;
      }
      cout << endl;
      int sum;
      cin >> sum;
      return sum;
#endif
    };

    auto query2 = [&](int u) -> void {
      Q++;
#ifdef ETHANKIM8683
      A[u] = -A[u];
#else
      cout << "? 2 " << u + 1 << endl;
#endif
    };

    auto answer = [&](vector<int> V) -> void {
#ifdef ETHANKIM8683
      bool ok = Q <= N + 200;
      for (int i = 0; i < N; i++) {
        ok = ok and V[i] == A[i];
      }
      cout << (ok ? "passed" : "failed") << endl;
#else
      cout << '!';
      for (auto e : V) {
        cout << ' ' << e;
      }
      cout << endl;
#endif
    };

    auto [r_, adj_] = centroid_decomp(adj);
    auto solve = [&](auto self, int a) -> int {
      if (adj_[a].size() == 0) return a;

      auto check = [&](int k) -> bool {
        vector<int> U;
        for (int i = 0; i < k; i++) {
          U.push_back(adj_[a][i]);
        }
        int sum = query1(U);
        query2(a);
        int sum_ = query1(U);
        return (sum + sum_ + k) % 2 == 0;
      };
      int l = 0, r = adj_[a].size();
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        check(m) ? l = m : r = m - 1;
      }

      if (l == 0) {
        int sum = query1({a});
        query2(adj_[a][l]);
        int sum_ = query1({a});
        if (sum == sum_) return a;
      }

      return self(self, adj_[a][l]);
    };
    int r = solve(solve, r_);

    vector<int> par(N);
    auto dfs = [&](auto self, int a, int p) -> void {
      par[a] = p;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    dfs(dfs, r, -1);

    vector<int> sum(N);
    for (int i = 0; i < N; i++) {
      sum[i] = query1({i});
    }

    vector<int> ans(N);
    for (int i = 0; i < N; i++) {
      int p = par[i];
      ans[i] = p == -1 ? sum[i] : sum[i] - sum[p];
    }
    answer(ans);
  }
}