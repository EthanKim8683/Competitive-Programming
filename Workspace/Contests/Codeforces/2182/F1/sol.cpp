#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;
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

const int MAXN = 3e5;
const int MAXQ = 3e5;
const int MAXX = 60;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vc<mint> fact(MAXN + MAXQ + 1), inv_fact(MAXN + MAXQ + 1);
  fact[0] = inv_fact[0] = 1;
  rep(i, 1, MAXN + MAXQ + 1) {
    fact[i] = fact[i - 1] * i;
    inv_fact[i] = inv_fact[i - 1] / i;
  }

  auto binom = [&](int n, int k) -> mint {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n - k];
  };

  vc<mint> pows(MAXN + MAXQ + 1);
  pows[0] = 1;
  rep(i, 1, MAXN + MAXQ + 1) { pows[i] = pows[i - 1] * 2; }

  int N, M;
  cin >> N >> M;

  vi C(N);
  for (auto &e : C) cin >> e;

  // basically digit dp

  vi counts(MAXX + 1, 0);
  for (auto e : C) {
    counts[e]++;
  }

  while (M--) {
    int t, x;
    cin >> t >> x;

    if (t == 1) {
      counts[x]++;
    } else if (t == 2) {
      counts[x]--;
    } else if (t == 3) {
      vi bits;
      rep(i, 0, MAXX + 1) {
        if (~x >> (MAXX - i) & 1) continue;
        bits.pb(MAXX - i + sz(bits));
      }

      vi usage(MAXX + 1, 0);
      for (auto e : bits) {
        usage[e]++;
      }

      mint ans = 0;
      auto contribute = [&](int i) -> void {
        mint sum = 1;

        rep(j, 0, i) { sum *= pows[counts[j]]; }

        mint count = pows[counts[i]];
        rep(j, 0, usage[i]) { count -= binom(counts[i], j); }
        sum *= count;

        rep(j, i + 1, MAXX + 1) { sum *= binom(counts[j], usage[j]); }

        ans += sum;
      };
      rep(i, bits.back() + 1, MAXX + 1) {
        usage[i]++;
        contribute(i);
        usage[i]--;
      }
      contribute(bits.back());
      cout << ans.val() << '\n';
    }
  }
}
