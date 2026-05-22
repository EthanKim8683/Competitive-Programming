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

  // is ev fine?? no cuz adaptive duh

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto query = [&](int u, int v) -> bool {
      cout << u + 1 << ' ' << v + 1 << endl;
      int x;
      cin >> x;
      return x == 1;
    };

    vc<pii> queries;
    rep(i, 1, N) {
      rep(j, 0, N - i) { queries.eb(j, j + i); }
    }
    for (auto [u, v] : queries) {
      if (query(u, v)) break;
    }
  }
}
