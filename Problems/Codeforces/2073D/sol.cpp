#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

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

const int MOD = 998244353;

struct S {
  int p[3], cost[3];
};
S op(S a, S b) {
  S rv;
  rep(i, 0, 3) {
    rv.p[i] = a.p[b.p[i]];
    rv.cost[i] = (a.cost[b.p[i]] + b.cost[i]) % MOD;
  }
  return rv;
}
S e() { return {{0, 1, 2}, {0, 0, 0}}; }

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vi P(N);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
      if (y & 1) {
        (rv *= x) %= MOD;
      }
    }
    return rv;
  };
  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  vc<S> st(2 * N, e());
  auto assign = [&](int i, S v) -> void {
    for (st[i += N] = v; i >>= 1;) {
      st[i] = op(st[i << 1], st[i << 1 | 1]);
    }
  };
  auto query = [&](int l, int r) -> S {
    S lv = e(), rv = e();
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, st[l++]);
      if (r & 1) rv = op(st[--r], rv);
    }
    return op(lv, rv);
  };

  auto assign2 = [&](int i, int v) -> void {
    S v2;
    rep(j, 0, 3) {
      if (j == v) {
        v2.p[j] = j;
        v2.cost[j] = 0;
      } else {
        v2.p[j] = 3 - (j + v);
        v2.cost[j] = mod_pow(2, i);
      }
    }
    assign(i, v2);
  };
  auto query2 = [&](int l, int r) -> int {
    return query(l, r).cost[0] * mod_inv(mod_pow(2, l)) % MOD;
  };

  rep(i, 0, N) { assign2(i, P[i]); }

  while (Q--) {
    char t;
    cin >> t;

    if (t == 'c') {
      int x, y;
      cin >> x >> y;
      x--, y--;

      assign2(x, y);
    } else {
      int l, r;
      cin >> l >> r;
      l--;

      cout << query2(l, r) << '\n';
    }
  }
}
