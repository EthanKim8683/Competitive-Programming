#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
// TODO: Make "ethankim8683/algebra" C++17 compliant
// #include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> cows(N);
  for (auto &e : cows) cin >> e;

  vector<mint> fact(K + 1);
  fact[0] = 1;
  for (int i = 1; i <= K; i++) {
    fact[i] = fact[i - 1] * i;
  }

  vector binom(K + 1, vector<mint>(K + 1));
  for (int i = 0; i <= K; i++) {
    for (int j = 0; j <= i; j++) {
      binom[i][j] = fact[i] / (fact[i - j] * fact[j]);
    }
  }

  vector<mint> inv(K + 1);
  for (int i = 1; i <= K; i++) {
    inv[i] = (mint) 1 / i;
  }

  vector<mint> ans(1 << K, 0);
  for (int i = 0; i < K; i++) {
    vector<mint> sos(1 << K, 0);
    for (auto e : cows) {
      if (e >> i & 1) {
        sos[e]++;
      }
    }

    for (int j = 0; j < K; j++) {
      for (int k = 0; k < (1 << K); k++) {
        if (k >> j & 1) {
          sos[k] += sos[k ^ 1 << j];
        }
      }
    }

    vector<mint> sos_(1 << K, 0);
    for (int j = (1 << K) - 1; j >= 1; j--) {
      int pc = __builtin_popcount(j);
      mint pie = 0;
      for (int k = 0; k <= K - pc; k++) {
        pie += (k % 2 == 0 ? 1 : -1) * binom[K - pc][k] * inv[pc + k];
      }
      sos_[j] += pie * sos[j];
    }

    for (int j = 0; j < K; j++) {
      for (int k = (1 << K) - 1; k >= 0; k--) {
        if (~k >> j & 1) {
          sos_[k] += sos_[k ^ 1 << j];
        }
      }
    }

    for (int j = 0; j < (1 << K); j++) {
      if (j >> i & 1) {
        ans[j] += sos_[j];
      }
    }
  }
  for (auto e : cows) {
    cout << ans[e].val() << '\n';
  }

  // for (auto e : cows) {
  //   mint ans = 0;
  //   for (auto f : cows) {
  //     ans += (mint) __builtin_popcount(e & f) / __builtin_popcount(e | f);
  //   }
  //   cerr << ans.val() << '\n';
  // }
}
