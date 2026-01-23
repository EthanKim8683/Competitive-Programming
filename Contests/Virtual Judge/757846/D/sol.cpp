#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // ps

  string S;
  cin >> S;

  char bases[] = "ATGC";

  vc ps(4, vi(sz(S) + 1, 0));
  rep(i, 0, sz(S)) {
    int j = find(all(bases), S[i]) - begin(bases);
    ps[j][i + 1] = 1;
  }
  rep(i, 0, 4) {
    rep(j, 0, sz(S)) { ps[i][j + 1] += ps[i][j]; }
  }

  int M;
  cin >> M;

  rep(_i, 0, M) {
    int s, e;
    cin >> s >> e;
    s--;

    vc<pii> counts;
    rep(i, 0, 4) { counts.eb(-(ps[i][e] - ps[i][s]), i); }
    sort(all(counts));
    for (auto [_count, i] : counts) {
      cout << bases[i];
    }
    cout << '\n';
  }
}