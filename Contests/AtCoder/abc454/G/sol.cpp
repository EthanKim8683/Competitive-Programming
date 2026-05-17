#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/tree.hpp"
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // the editorial solution is really brilliant

  int N, seed, M, F;
  cin >> N >> seed >> M >> F;

  vi Q(M);
  rep(i, 1, M) {
    cin >> Q[i];
    Q[i]--;
  }

  vi D(M);
  for (auto &e : D) {
    cin >> e;
    e--;
  }

  int state = seed;

  vi P(N);
  rep(i, 1, N) {
    if (i < M) {
      P[i] = Q[i];
    } else {
      P[i] = state % i;
      state = (state * 1103515245 + 12345) % (1ll << 31);
    }
  }

  vi C(N);
  rep(i, 0, N) {
    if (i < M) {
      C[i] = D[i];
    } else {
      C[i] = state % F;
      state = (state * 1103515245 + 12345) % (1ll << 31);
    }
  }

  vc<vc<signed>> adj(N);
  rep(i, 1, N) { adj[P[i]].pb(i); }

  vc<pii> by_color(N, {0, 0}), by_count(N + 1, {0, 0});
  pii m = {0, 0};
  int t = 0;
  auto fix = [&](pii &x) -> void {
    if (x.sd == t) return;
    x = {0, t};
  };
  mint ans = 0;
  sack(
      [&](int a) -> void {
        fix(by_color[C[a]]);
        fix(by_count[by_color[C[a]].fs]);
        by_count[by_color[C[a]].fs].fs -= 1;
        by_color[C[a]].fs += 1;
        fix(by_count[by_color[C[a]].fs]);
        by_count[by_color[C[a]].fs].fs += 1;
        fix(m);
        chmax(m.fs, by_color[C[a]].fs);
      },
      [&]() -> void { t += 1; },
      [&](int a) -> void {
        fix(m);
        fix(by_count[m.fs]);
        int k = by_count[m.fs].fs;
        ans += (m.fs ^ (a + 1)) * (k ^ (a + 1));
      },
      adj, 0);
  cout << ans.val() << '\n';
}
