#include <bits/stdc++.h>

#include "atcoder/modint"

using namespace std;
using namespace atcoder;
using mint = modint998244353;
using i64 = long long;

const int MAXH = 2e5;
const int MAXW = 2e5;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<mint> fact(MAXW + MAXH + 1);
  fact[0] = 1;
  for (int i = 1; i <= MAXW + MAXH; i++) {
    fact[i] = fact[i - 1] * i;
  }

  auto binom = [&](int n, int k) -> mint {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return fact[n] / (fact[k] * fact[n - k]);
  };

  int T;
  cin >> T;

  while (T--) {
    int H, W, K;
    cin >> H >> W >> K;

    if (K < H + W - 2) {
      cout << "0\n";
    } else if (K == H + W - 2) {
      cout << binom(H - 1 + W - 1, H - 1).val() << '\n';
    } else if (K == H + W - 1) {
      i64 n = (i64) H * (W - 1) + (i64) W * (H - 1) - (H - 1 + W - 1);
      cout << (binom(H - 1 + W - 1, H - 1) * n).val() << '\n';
    } else {
      i64 n = (i64) H * (W - 1) + (i64) W * (H - 1) - (H - 1 + W - 1);
      mint ans = 0;
      ans += binom(H - 1 + W - 1, H - 1) * n * (n - 1) / 2 -
             binom(H - 2 + W - 2, H - 2) * (H - 2 + W - 2 + 1);
      ans += (W - 1 + 2 - 2) * binom(H - 1 - 2 + W - 1 + 2, H - 1 - 2);
      ans += (H - 1 + 2 - 2) * binom(H - 1 + 2 + W - 1 - 2, H - 1 + 2);
      cout << (ans).val() << '\n';
    }
  }
}