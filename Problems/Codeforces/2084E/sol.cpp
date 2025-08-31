#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;
using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + (A[i] == -1);
    }
    int H = ps[N] - ps[0];

    // auto f = [&](int K, int h, int u) -> mint {
    //   // return binom<mint>(h, K + 1 - u) * fact<mint>(K + 1 - u) *
    //   //        fact<mint>(H - (K + 1 - u));

    //   int t = K + 1 - u;
    //   return fact<mint>(h) / fact<mint>(h - t) * fact<mint>(H - t);
    // };

    // mint ans = 0;
    // for (int K = 0; K < N; K++) {
    //   int L = N, R = 0, u = 0;
    //   for (int i = 0; i < N; i++) {
    //     if (A[i] != -1 and A[i] <= K) {
    //       L = min(L, i);
    //       R = max(R, i);
    //       u++;
    //     }
    //   }

    //   for (int l = 0; l < N; l++) {
    //     for (int r = l; r < N; r++) {
    //       int h = ps[r + 1] - ps[l];
    //       if (l <= L and r >= R and h >= K + 1 - u) {
    //         ans += f(K, h, u);
    //       }
    //     }
    //   }
    // }
    // cout << ans.val() << '\n';

    for (int K = 0; K < N; K++) {
      int L = N, R = 0, u = 0;
      for (int i = 0; i < N; i++) {
        if (A[i] != -1 and A[i] <= K) {
          L = min(L, i);
          R = max(R, i);
          u++;
        }
      }

      for (int i = 0; i < N; i++) {
        if (i <= L) {
          int l = i;
        }

        if (i >= R) {
          int r = i;
        }
      }
    }
  }
}
