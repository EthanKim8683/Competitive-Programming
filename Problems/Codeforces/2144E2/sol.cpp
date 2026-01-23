#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

using S = mint;
S op(S a, S b) { return a + b; }
S e() { return 0; }
using F = int;
S mapping(F f, S x) { return x * mint(2).pow(f); }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> L;
    L.push_back(-1);
    for (auto e : A) {
      if (e > L.back()) {
        L.push_back(e);
      }
    }
    vector<int> R;
    for (int i = N - 1; i >= 0; i--) {
      if (R.empty() or A[i] > R.back()) {
        R.push_back(A[i]);
      }
    }

    auto index = [&](vector<int> &B, int x) -> pair<bool, int> {
      int i = lower_bound(B.begin(), B.end(), x) - B.begin();
      return {B[i] == x, i};
    };

    lazy_segtree<S, op, e, F, mapping, composition, id> st1(L.size()),
        st2(R.size());
    st1.set(0, 1);
    for (auto e : A) {
      {
        auto [exact, i] = index(R, e);
        if (!exact) {
          st2.apply(i + 1, R.size(), 1);
        } else if (i == R.size() - 1) {
          st2.set(i, st2.get(i) + st1.get(L.size() - 1));
          st2.set(i, st2.get(i) + st1.get(L.size() - 2));
        } else {
          mint carry = st2.get(i + 1);
          st2.apply(i + 1, R.size(), 1);
          st2.set(i, st2.get(i) + carry);
        }
      }
      {
        auto [exact, i] = index(L, e);
        if (!exact) {
          st1.apply(i, L.size(), 1);
        } else {
          mint carry = st1.get(i - 1);
          st1.apply(i, L.size(), 1);
          st1.set(i, st1.get(i) + carry);
        }
      }
    }
    cout << st2.get(0).val() << '\n';
  }
}
