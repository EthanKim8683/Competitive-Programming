#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    int N = S.size();

    vector ft1(2, fenwick_tree<mint>(N)), ft2 = ft1;
    mint ans = mint(2).pow(N) - 1;
    auto change = [&](int i, int v, int sign) -> void {
      ans += sign * mint(2).pow(i) * ft2[1 - v].sum(i + 1, N);
      ans += sign * ft1[1 - v].sum(0, i) * mint(2).pow(N - 1 - i);
      ft1[v].add(i, sign * mint(2).pow(i));
      ft2[v].add(i, sign * mint(2).pow(N - 1 - i));
    };
    for (int i = 0; i < N; i++) {
      change(i, S[i] - '0', 1);
    }

    int Q;
    cin >> Q;

    while (Q--) {
      int v;
      cin >> v;
      v--;

      change(v, S[v] - '0', -1);
      S[v] ^= 1;
      change(v, S[v] - '0', 1);

      cout << ans.val() << ' ';
    }
    cout << '\n';
  }
}
