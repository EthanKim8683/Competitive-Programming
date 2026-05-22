#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> S(N);
    for (auto &e : S) cin >> e;

    int K = S[N - 1];

    vector<pair<int, mint>> F;
    mint ans = 0;
    for (int x = 1; x <= K; x++) {
      int f = K / x, c = (K - 1) / x + 1;
      if (f == c) {
        for (auto e : S) {
          if (e % f == 0) {
            ans += x;
          }
        }
        continue;
      }
      if (F.empty() or F.back().first != f) {
        F.push_back({f, 0});
      }
      F.back().second += x;
    }

    vector<mint> ps(K + 1, 0);
    for (auto [f, count] : F) {
      int c = f + 1;
      for (int i = 0; i < f and i * f <= K; i++) {
        ps[i * f] += count;
        if (i * c + 1 <= K) {
          ps[i * c + 1] -= count;
        }
      }
      if ((i64) f * f <= K) {
        ps[f * f] += count;
      }
    }
    for (int i = 0; i < K; i++) {
      ps[i + 1] += ps[i];
    }

    for (auto e : S) {
      ans += ps[e];
    }
    cout << ans.val() << '\n';
  }
}
