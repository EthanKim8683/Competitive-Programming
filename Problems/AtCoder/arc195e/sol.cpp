#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<int> A(N);
  for (int i = 1; i < N; i++) {
    cin >> A[i];
  }

  vector<mint> dtr(N);
  mint ps = 0;
  for (int i = 1; i < N; i++) {
    dtr[i] = ps / i + A[i];
    ps += dtr[i];
  }
  for (auto &e : dtr) {
    e *= fact<mint>(N - 1);
  }

  while (Q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    mint d = 0, dtrw = 0;
    for (int i = 1; i < u; i++) {
      dtrw += (d + A[i]) * 1 * (fact<mint>(u - 1) / fact<mint>(i)) *
              (fact<mint>(v - 1) / fact<mint>(u));
      d = (d + 0) * (i - 1) + (d + A[i]) * 1;
    }

    cout << (dtr[u] + dtr[v] - 2 * dtrw).val() << '\n';
  }
}
