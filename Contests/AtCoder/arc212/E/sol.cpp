#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/combinatorics.hpp"
#include "ethankim8683/data_structures.hpp"
using namespace ethankim8683;

using mint = modint998244353;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi P(N);
  for (auto &e : P) cin >> e;

  vc<pii> V(N);
  rep(i, 0, N) { V[i] = {P[i], i}; }
  using S = pii;
  auto op = [&](S a, S b) -> S { return max(a, b); };
  auto e = [&]() -> S { return {-INF, -1}; };
  sparse_table<S, op, e> st(V);
  auto dfs = [&](auto self, int l, int r) -> mint {
    if (l >= r) return 1;
    int m = st.prod(l, r).sd;
    mint rv = 1;
    rv *= self(self, l, m);
    rv *= self(self, m + 1, r);
    int n1 = m - l, n2 = r - (m + 1);
    if (l > 0 and r < N) {
      rv *= binom<mint>(n1 + n2 + 1, n1 + 1) +
            binom<mint>(n1 + n2 + 1, n2 + 1) - binom<mint>(n1 + n2, n1);
    } else if (l > 0) {
      rv *= binom<mint>(n1 + n2 + 1, n1 + 1);
    } else if (r < N) {
      rv *= binom<mint>(n1 + n2 + 1, n2 + 1);
    } else {
      rv *= binom<mint>(n1 + n2, n1);
    }
    return rv;
  };
  cout << dfs(dfs, 0, N).val() << '\n';
}
