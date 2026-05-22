#include <bits/stdc++.h>

#include "atcoder/modint"

using namespace std;
using namespace atcoder;
using mint = modint998244353;

const int LOGA = 20;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<mint> seen(1 << LOGA, 1);
  for (auto e : A) {
    int L = e & ((1 << (LOGA / 2)) - 1), U = e ^ L;

    for (int i = L; i < (1 << (LOGA / 2)); i = (i + 1) | L) {
      seen[U | i] *= e;
    }

    mint ans = 1;
    for (int i = U; i > 0; i = (i - 1) & U) {
      ans *= seen[i | L];
    }
    ans *= seen[0 | L];
    cout << ans.val() << '\n';
  }
}