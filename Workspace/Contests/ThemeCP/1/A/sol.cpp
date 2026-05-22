#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vector<mint> fs(M);
    for (auto &k_mint : fs) {
      int a, b, k;
      cin >> a >> b >> k;
      k_mint = (mint) k;
    }

    mint dev = 0;
    for (auto k : fs) {
      dev += k / ((mint) N * (N - 1) / 2);
    }
    mint ev = 0;
    for (int i = 0; i < K; i++) {
      ev += dev;
      dev += M / ((mint) N * (N - 1) / 2).pow(2);
    }
    cout << ev.val() << '\n';
  }
}
/*

*/
