#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;
using i64 = long long;

// My first DMOJ contest! Hope I do alright!
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    i64 A, B;
    cin >> A >> B;
    if (A > B) swap(A, B);

    auto isqrt = [&](i64 x) -> int {
      int l = 0, r = 2e9;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        (i64) m *m <= x ? l = m : r = m - 1;
      }
      return l;
    };
    auto sos = [&](mint n) -> mint { return n * (n + 1) * (2 * n + 1) / 6; };

    mint sqrtA = isqrt(A), sqrtB = isqrt(B), sqrtAB = isqrt(A + B);
    // cerr << sqrtA.val() << ' ' << sqrtB.val() << ' ' << sos(sqrtA).val() << '
    // '
    //      << sos(sqrtB).val() << ' ' << '\n';
    cout << (1 + sos(sqrtA) + sqrtA + (sqrtB - sqrtA) * (A + 1) -
             (sos(sqrtAB) - sos(sqrtB)) + (A + B + 1) * (sqrtAB - sqrtB))
                .val()
         << '\n';
  }
}
