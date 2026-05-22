#ifndef U
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<string> sheet(N);
    for (auto &e : sheet) cin >> e;

    vc<vc<pii>> snakes(26);
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (sheet[i][j] == '.') continue;
        snakes[sheet[i][j] - 'a'].eb(i, j);
      }
    }

    for (int i = 26 - 1; i - 1 >= 0; i--) {
      if (snakes[i].empty()) continue;
      if (snakes[i - 1].empty()) {
        snakes[i - 1].pb(snakes[i][0]);
      }
    }

    bool ok = true;
    vc<tuple<int, int, int, int>> ans;
    rep(i, 0, 26) {
      if (snakes[i].empty()) break;
      int di = 0, dj = 0;
      rep(j, 0, sz(snakes[i]) - 1) {
        auto [i1, j1] = snakes[i][j];
        auto [i2, j2] = snakes[i][j + 1];
        int di2 = i2 - i1, dj2 = j2 - j1, g = gcd(di2, dj2);
        di2 /= g;
        dj2 /= g;
        if (di == 0 and dj == 0) {
          di = di2;
          dj = dj2;
        } else {
          ok = ok and di2 == di;
          ok = ok and dj2 == dj;
        }
      }
      ok = ok and (di == 0 or dj == 0);
      auto [i1, j1] = snakes[i].front();
      auto [i2, j2] = snakes[i].back();
      ans.eb(i1, j1, i2, j2);
    }

    vc simulation(N, string(M, '.'));
    rep(k, 0, sz(ans)) {
      auto [i1, j1, i2, j2] = ans[k];
      int di = i2 - i1, dj = j2 - j1, g = gcd(di, dj);
      if (g != 0) {
        di /= g;
        dj /= g;
      }
      int i = i1, j = j1;
      while (true) {
        simulation[i][j] = (char) (k + 'a');
        if (i == i2 and j == j2) break;
        i += di;
        j += dj;
      }
    }
    ok = ok and simulation == sheet;

    if (!ok) {
      cout << "NO\n";
      continue;
    }

    cout << "YES\n";
    cout << sz(ans) << '\n';
    for (auto [r1, c1, r2, c2] : ans) {
      cout << r1 + 1 << ' ' << c1 + 1 << ' ' << r2 + 1 << ' ' << c2 + 1 << '\n';
    }
  }
}
