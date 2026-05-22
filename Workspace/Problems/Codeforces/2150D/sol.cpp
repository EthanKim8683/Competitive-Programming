#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // inner clusters have odd size
  // can make inner clusters of any odd size
  // can make outer clusters of any size
  // clusters form a contiguous range
  // can shift clusters to any position

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<mint> ps1(N + 1, 0), ps2(N + 1, 0);
    ps2[0] += N;
    for (int i = 2; i <= N; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          int n = N - i - j - k;
          if (!(n >= 0 and n % 2 == 0)) continue;
          mint count = binom<mint>(n / 2 + i - 1, i - 1),
               sum = count * (1 + (mint) n / i);
          ps1[0] += sum;
          ps1[i] -= sum;
          ps1[N - i + 1] -= sum;
          ps2[0] += j * count;
          ps2[N - i + 1] -= j * count;
          ps2[i - 1] += k * count;
        }
      }
    }
    for (int i = 0; i < N; i++) {
      ps1[i + 1] += ps1[i];
    }
    for (int i = 0; i < N; i++) {
      ps2[i] += ps1[i];
    }
    for (int i = 0; i < N; i++) {
      ps2[i + 1] += ps2[i];
    }
    mint ans = 0;
    for (int i = 0; i < N; i++) {
      ans += A[i] * ps2[i];
    }
    cout << ans.val() << '\n';
  }
}
