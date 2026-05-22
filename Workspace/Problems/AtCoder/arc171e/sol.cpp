#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, A, B;
  cin >> N >> M >> A >> B;
  A--, B--;

  if (M % 2 == 1) {
    cout << 0;
    exit(0);
  }

  auto solve = [&](int x) -> mint {
    mint rv = 0;
    for (int i = 0; 2 * i <= x; i++) {
      rv += binom<mint>(x - i, i) *
            binom<mint>(N - (x + 2) - (M / 2 - 1 - i), M / 2 - 1 - i) *
            binom<mint>(M / 2 - 2, i) * fact<mint>(i) *
            fact<mint>(M / 2 - 1 - i);
    }
    for (int i = 0; 2 * i <= x - 1; i++) {
      rv += binom<mint>(x - 1 - i, i) *
            binom<mint>(N - (x + 1) - (M / 2 - 1 - i), M / 2 - 1 - i) *
            binom<mint>(M / 2 - 2, i - 1) * fact<mint>(i) *
            fact<mint>(M / 2 - 1 - i);
    }
    return rv;
  };
  cout << (2 * solve(A) * solve(B)).val();
}
