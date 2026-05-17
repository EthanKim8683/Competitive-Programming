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

map<string, vc<string>> adj;

array<pii, 2> dfs(string a) {
  array<pii, 2> rv;
  rv[0] = {0, 1};
  rv[1] = {1, 1};
  for (auto b : adj[a]) {
    auto t = dfs(b);
    if (t[0].fs == t[1].fs) {
      rv[0].fs += t[0].fs;
      rv[0].sd *= t[0].sd + t[1].sd;
    } else if (t[0].fs > t[1].fs) {
      rv[0].fs += t[0].fs;
      rv[0].sd *= t[0].sd;
    } else if (t[1].fs > t[0].fs) {
      rv[0].fs += t[1].fs;
      rv[0].sd *= t[1].sd;
    }
    rv[1].fs += t[0].fs;
    rv[1].sd *= t[0].sd;
  }
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  while (true) {
    int N;
    cin >> N;
    if (N == 0) break;

    string big_boss;
    cin >> big_boss;

    adj.clear();
    rep(i, 0, N - 1) {
      string a, b;
      cin >> a >> b;

      adj[b].pb(a);
    }

    auto [f, s] = dfs(big_boss);
    int m, n;
    if (f.fs == s.fs) {
      m = f.fs;
      n = f.sd + s.sd;
    } else if (f.fs > s.fs) {
      m = f.fs;
      n = f.sd;
    } else if (s.fs > f.fs) {
      m = s.fs;
      n = s.sd;
    }
    cout << m << ' ' << (n != 1 ? "No" : "Yes") << '\n';
  }
}
