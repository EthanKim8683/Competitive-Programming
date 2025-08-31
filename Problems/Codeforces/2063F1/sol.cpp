#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/modint.hpp"
#include "atcoder/segtree.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int MAXN = 3e5;

int op(int a, int b) { return max(a, b); }
int e() { return -1; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<mint> fact(4 * MAXN + 1);
  fact[0] = 1;
  for (int i = 1; i <= 4 * MAXN; i++) {
    fact[i] = fact[i - 1] * i;
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<pair<int, int>> clues(N);
    for (auto &[l, r] : clues) {
      cin >> l >> r;
      r++;
    }

    int l0 = 0, r0 = 2 * N + 2;

    segtree<int, op, e> st(2 * N + 2);
    st.set(l0, r0);
    auto find_parent = [&](int l, int r) -> pair<int, int> {
      int s = 0, t = l;
      while (s < t) {
        int m = s + (t - s + 1) / 2;
        st.prod(m, l) > r ? s = m : t = m - 1;
      }
      return {s, st.get(s)};
    };

    fenwick_tree<int> used(2 * N + 2);
    auto solve = [&](int l, int r) -> mint {
      return num_balanced_bracket_seqs<mint>((r - l - 2) -
                                             used.sum(l + 1, r - 1));
    };

    mint ans = solve(l0, r0);
    cout << ans.val() << ' ';
    for (auto [l, r] : clues) {
      auto [l2, r2] = find_parent(l, r);
      ans /= solve(l2, r2);

      ans *= solve(l, r);
      int dv = r - l - used.sum(l + 1, r - 1);
      used.add(l, dv);
      used.add(l2, -dv);
      st.set(l, r);

      ans *= solve(l2, r2);

      cout << ans.val() << ' ';
    }
    cout << '\n';
  }
}
