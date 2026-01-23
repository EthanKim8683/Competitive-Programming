#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = dynamic_modint<0>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, P;
    cin >> N >> M >> P;

    mint::set_mod(P);

    mint f = (mint) 1 / M;
    vector<mint> pows = {1};
    for (int i = 1; i <= N / 2; i++) {
      pows.push_back(pows.back() * f);
    }

    mint indep = 0;
    for (int i = 1; i <= N; i++) {
      indep += (N - i + 1) * pows[i / 2];
    }
    mint ans = indep * indep;
    vector<mint> ps(2, 0);
    for (int i = 1; i <= N; i++) {
      ans += P - (N - i + 1) * pows[i / 2] * (2 * ps[i % 2] + pows[i / 2]);
      ans += (i64) ((i + 1) / 2 * 2 - 1) * (N - i + 1) * pows[i / 2];
      ps[i % 2] += pows[i / 2];
    }
    cout << ans.val() << '\n';
  }
}
