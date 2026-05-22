#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> restrictions(M);
    for (auto &[i, x] : restrictions) {
      cin >> i >> x;
      i--, x--;
    }

    vector<vector<int>> indices(2 * N);
    for (auto [i, x] : restrictions) {
      indices[N + x - i].push_back(i);
    }
    for (auto &r : indices) {
      sort(r.begin(), r.end());
    }

    auto first = [&](int x, int i) -> int {
      if (!(0 <= N + x and N + x < 2 * N)) return N;
      auto it = lower_bound(indices[N + x].begin(), indices[N + x].end(), i);
      return it == indices[N + x].end() ? N : *it;
    };

    vector<mint> dp1(N + 1, 0);
    vector ps(N + 1, vector<mint>(N + 2, 0)),
        dp2(N + 1, vector<mint>(N + 1, 0));
    dp1[0] = 1;
    for (int i = 0; i < N; i++) {
      int k = first(-i, i);
      for (int j = 1; i + j <= k; j++) {
        dp1[i + j] += dp1[i];
        dp2[i + j][j] += dp1[i];
      }
      for (int j = 1; j <= N; j++) {
        ps[j][i + 1] += dp1[i] - dp2[i][j];
        ps[j][first(j - i, i) + 1] -= dp1[i] - dp2[i][j];
      }
      for (int j = 1; i + j <= k; j++) {
        dp1[i + j] += ps[j][i];
      }
      for (int j = 0; j <= N; j++) {
        ps[j][i + 1] += ps[j][i];
      }
    }
    cout << dp1[N].val() << '\n';
  }
}
