#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

mint op(mint a, mint b) { return a + b; }
mint e() { return 0; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<mint> ans(N);
    segtree<mint, op, e> st(N);
    st.set(N - 1, 2);
    ans[N - 1] += 2 * mint(2).pow(N / 2);
    for (int i = N - 2; i >= 0; i--) {
      mint dp = st.prod(i + 1, min(2 * (i + 1) - 1, N));
      st.set(i, dp);
      ans[i] += dp * mint(2).pow((i + 1) / 2);
    }
    mint C = mint(2).pow(N);
    for (auto e : ans) {
      cout << (e / C).val() << '\n';
    }
  }
}
