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

  string S;
  cin >> S;

  string T;
  cin >> T;

  vc<vi> indices(26);
  rep(i, 0, sz(S)) { indices[S[i] - 'a'].pb(i); }

  int ans = 0, jmin = sz(S) + 1;
  for (int i = sz(S) - 1; i >= 0; i--) {
    int j = i;
    for (auto e : T) {
      auto it = lower_bound(all(indices[e - 'a']), j);
      if (it == indices[e - 'a'].end()) {
        j = sz(S) + 1;
        break;
      }
      j = *it + 1;
    }
    chmin(jmin, j);
    ans += jmin - (i + 1);
  }
  cout << ans << '\n';
}
