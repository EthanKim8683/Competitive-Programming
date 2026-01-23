#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

const int MAXQ = 5e3;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector binoms(MAXQ + 1, vector<mint>(MAXQ + 1));
  for (int i = 0; i <= MAXQ; i++) {
    for (int j = 0; j <= MAXQ; j++) {
      binoms[i][j] = binom<mint>(i, j);
    }
  }
  auto binom2 = [&](int n, int k) -> mint {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return binoms[n][k];
  };

  auto fact2 = fact<mint>;

  int T;
  cin >> T;

  while (T--) {
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<pair<int, int>> queries(Q);
    for (auto &[i, x] : queries) {
      cin >> i >> x;
      i--;
    }

    vector<int> A2;
    for (int i = 0; i < N; i++) {
      A2.push_back(A[i] - i);
    }

    vector<pair<int, int>> queries2;
    for (auto [i, x] : queries) {
      queries2.emplace_back(x - i, i);
    }
    sort(queries2.begin(), queries2.end());

    vector<mint> ans(N);
    for (int i = 0; i < N; i++) {
      int ltl = 0, ltm = 0, ltr = 0, gtl = 0, gtm = 0, gtr = 0;
      for (auto [h, i2] : queries2) {
        if (i2 < i) {
          gtl++;
        } else if (i2 == i) {
          gtm++;
        } else {
          gtr++;
        }
      }

      mint rest = fact2(Q);
      ans[i] = 0;
      for (auto [h, i2] : queries2) {
        mint count;
        if (i2 < i) {
          gtl--;
          // ltl, gtr can go wherever
          // ltm, ltr must go before current
          // gtl, gtm must go before ltm, ltr
          int x = ltl + gtr, y = ltm + ltr, z = gtl + gtm;
          count = (h > A2[i] or y >= 1 ? 1 : 0) *
                  (z >= 1 ? binom2(y - 1 + z, z) : 1) * binom2(Q, y + z + 1) *
                  fact2(x) * fact2(y) * fact2(z);
          ltl++;
        } else if (i2 == i) {
          gtm--;
          // ltl, gtr can go wherever
          // ltm, ltr, gtl, gtm must go before current
          int x = ltl + gtr, y = ltm + ltr + gtl + gtm;
          count = binom2(Q, y + 1) * fact2(x) * fact2(y);
          ltm++;
        } else {
          gtr--;
          // ltl, gtr can go wherever
          // gtl, gtm must go before current
          // ltm, ltr must go before gtl, gtm
          int x = ltl + gtr, y = gtl + gtm, z = ltm + ltr;
          count = (h < A2[i] or y >= 1 ? 1 : 0) *
                  (z >= 1 ? binom2(y - 1 + z, z) : 1) * binom2(Q, y + z + 1) *
                  fact2(x) * fact2(y) * fact2(z);
          ltr++;
        }
        ans[i] += h * count;
        rest -= count;
      }
      ans[i] += A2[i] * rest;
      ans[i] += i * fact2(Q);
    }

    for (auto e : ans) {
      cout << e.val() << ' ';
    }
    cout << '\n';
  }
}
