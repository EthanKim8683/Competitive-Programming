#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

const int MAXN = 1e4;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector dp1(MAXN + 1, vector<mint>(MAXN + 1, 0));
  dp1[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= j; k++) {
        dp1[i + 1][j - k + 1] += dp1[i][j] * binom<mint>(j, k);
      }
    }
  }

  // binom<mint>(j1, k1) * binom<mint>(j1 - k1 + 1, k2) * binom<mint>(j1 - k1 +
  // 1 - k2 + 1, k3) j1!/k1!/(j1-k1)! * (j1-k1+1)!/k2!/(j1-k1+1-k2)! * ...
  // j1!/k1! * (j1-k1+1)/k2! * (j1-k1+1-k2+1)/k3!

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<int> C(N);
    for (auto &e : C) {
      cin >> e;
      e--;
    }

    vector<int> mask(M);
    for (auto &e : mask) cin >> e;

    vector<int> counts(M, 0);
    for (auto e : C) {
      counts[e]++;
    }

    // num edges, num components
    // per color
  }
}
