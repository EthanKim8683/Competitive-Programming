#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

#ifdef ETHANKIM8683
    int R;
    cin >> R;
    R--;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
#endif

    auto query1 = [&](vector<int> U) -> int {
      cout << '?' << ' ' << 1 << ' ' << U.size();
      for (auto e : U) {
        cout << ' ' << e + 1;
      }
      cout << endl;
#ifdef ETHANKIM8683
      vector<int> sum(N);
      auto dfs = [&](auto self, int a, int d = 0, int p = -1) -> void {
        d += A[a];
        sum[a] = d;
        for (auto b : adj[a]) {
          if (b == p) continue;
          self(self, b, d, a);
        }
      };
      dfs(dfs, R);

      int rv = 0;
      for (auto e : U) {
        rv += sum[e];
      }
      return rv;
#else
      int rv;
      cin >> rv;
      return rv;
#endif
    };

    auto query2 = [&](int u) -> void {
      cout << '?' << ' ' << 2 << ' ' << u + 1 << endl;
#ifdef ETHANKIM8683
      A[u] = -A[u];
#endif
    };

    auto answer = [&](vector<int> V) -> void {
      cout << '!';
      for (auto e : V) {
        cout << ' ' << e;
      }
      cout << endl;
#ifdef ETHANKIM8683
      cerr << (equal(A.begin(), A.end(), V.begin(), V.end()) ? "PASSED"
                                                             : "FAILED")
           << endl;
#endif
    };

    auto check = [&](int x) -> bool {
      vector<int> U(adj[0].begin(), adj[0].begin() + x);
      int sum = query1(U);
      query2(0);
      int sum_ = query1(U);
      return abs(sum - sum_) != 2 * x;
    };
    int l = 1, r = adj[0].size();
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    int root;
    if (l == adj[0].size()) {
      int b = adj[0][adj[0].size() - 1], sum = query1({0});
      query2(b);
      int sum_ = query1({0});
      if (sum == sum_) {
        root = 0;
      } else {
        root = b;
      }
    } else {
      root = adj[0][l - 1];
    }

    vector<int> ps(N);
    for (int i = 0; i < N; i++) {
      ps[i] = query1({i});
    }

    vector<int> ans(N);
    auto dfs = [&](auto self, int a, int p = -1) -> void {
      if (p == -1) {
        ans[a] = ps[a];
      } else {
        ans[a] = ps[a] - ps[p];
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    dfs(dfs, root);

    answer(ans);
  }
}