#include <bits/stdc++.h>

using namespace std;

const int K = 18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, Z;
    cin >> N >> Z;

    vector<int> X(N);
    for (auto &e : X) cin >> e;

    int Q;
    cin >> Q;

    vector<pair<int, int>> queries(Q);
    for (auto &[l, r] : queries) {
      cin >> l >> r;
      l--;
    }

    vector anc1(N + 1, vector<int>(K + 1));
    anc1[N][0] = N;
    for (int i = 0; i < N; i++) {
      anc1[i][0] = upper_bound(X.begin(), X.end(), X[i] + Z) - X.begin();
    }
    for (int i = 1; i <= K; i++) {
      for (int j = 0; j <= N; j++) {
        anc1[j][i] = anc1[anc1[j][i - 1]][i - 1];
      }
    }

    vector anc2(N + 1, vector<pair<int, int>>(K + 1));
    anc2[N][0] = {N, 0};
    for (int i = 0; i < N; i++) {
      int a = i, d = 0;
      for (int j = K; j >= 0; j--) {
        int b = i + 1;
        for (int k = K; k >= 0; k--) {
          if (anc1[b][k] <= anc1[a][j]) {
            b = anc1[b][k];
          }
        }

        if (b != anc1[a][j]) {
          a = anc1[a][j];
          d += 1 << j;
        }
      }
      a = anc1[a][0];
      d += 1;

      int b = i + 1;
      for (int j = K; j >= 0; j--) {
        if (anc1[b][j] <= a) {
          b = anc1[b][j];
          d += 1 << j;
        }
      }

      anc2[i][0] = {a, d};
    }
    for (int i = 1; i <= K; i++) {
      for (int j = 0; j <= N; j++) {
        auto [p1, d1] = anc2[j][i - 1];
        auto [p2, d2] = anc2[p1][i - 1];
        anc2[j][i] = {p2, d1 + d2};
      }
    }

    for (auto [l, r] : queries) {
      int a = l, ans = 2;
      for (int i = K; i >= 0; i--) {
        auto [p, d] = anc2[a][i];
        if (p < r) {
          a = p;
          ans += d;
        }
      }

      int b = a + 1;
      if (b >= r) {
        ans--;
      } else {
        for (int i = K; i >= 0; i--) {
          if (anc1[a][i] < r) {
            a = anc1[a][i];
            ans += 1 << i;
          }
          if (anc1[b][i] < r) {
            b = anc1[b][i];
            ans += 1 << i;
          }
        }
      }

      cout << ans << '\n';
    }
  }
}
