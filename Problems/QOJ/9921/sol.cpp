#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
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

const int MAXM = 1e6;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 9:57
  // thinking done: 10:20
  // target impl time: 30 min
  // initial impl done: 10:50

  vc<vi> divisors(MAXM + 1);
  for (int i = 1; i <= MAXM; i++) {
    for (int j = i; j <= MAXM; j += i) {
      divisors[j].pb(i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<string> S(N);
    for (auto &e : S) cin >> e;

    vi st(2 * (N + 1), 0);
    auto add = [&](int i, int x) -> void {
      for (st[i += N] += x; i >>= 1;) {
        st[i] = st[i << 1] ^ st[i << 1 | 1];
      }
    };
    auto prod = [&]() -> int { return st[1]; };

    vc<vc<int>> adj;
    vi size;
    auto push = [&]() -> int {
      int rv = sz(adj);
      adj.pb(vc<int>(26, -1));
      size.pb(0);
      return rv;
    };
    push();
    auto insert = [&](string s) -> void {
      int a = 0;
      rep(i, 0, sz(s)) {
        auto &b = adj[a][s[i] - 'a'];
        if (b == -1) {
          b = push();
        }
        a = b;
        size[a]++;
        for (auto e : divisors[size[a]]) {
          add(e, e);
        }
      }
    };

    for (int i = 0; i < N; i++) {
      insert(S[i]);
      cout << prod() << ' ';
    }
    cout << '\n';
  }
}
