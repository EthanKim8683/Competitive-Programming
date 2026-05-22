#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<string> S(N);
  for (auto &e : S) cin >> e;

  vector queries(N, vector<vector<tuple<int, int, int>>>(N));
  for (int i = 0; i < Q; i++) {
    int U, D, L, R;
    cin >> U >> D >> L >> R;
    U--, D--, L--;
    queries[U][D].push_back({L, R, i});
  }

  vector<int> ans(Q);
  for (int u = 0; u < N; u++) {
    vector ps(N + 1, 0);
    for (int d = u + 1; d < N; d++) {
      vector ps_(N + 1, 0);
      for (int r = 1; r < N; r++) {
        if (S[d - 1][r - 1] == '.' and S[d - 1][r] == '.' and
            S[d][r - 1] == '.' and S[d][r] == '.') {
          ps_[r + 1] = 1;
        }
      }
      for (int i = 0; i < N; i++) {
        ps_[i + 1] += ps_[i];
        ps[i + 1] += ps_[i + 1];
      }

      for (auto [L, R, i] : queries[u][d]) {
        ans[i] = ps[R] - ps[L + 1];
      }
    }
  }
  for (auto e : ans) {
    cout << e << '\n';
  }
}