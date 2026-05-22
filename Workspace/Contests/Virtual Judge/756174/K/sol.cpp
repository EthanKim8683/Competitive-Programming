#include <bits/stdc++.h>

#include <algorithm>
using namespace std;

#define int long long
#define float long double
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
typedef pair<float, float> vec;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string S;
  cin >> S;

  int N = S.size();

  vc ps(26, vi(N + 1, 0));
  rep(i, 0, N) { ps[S[i] - 'a'][i + 1] += 1; }
  rep(i, 0, 26) {
    rep(j, 0, N) { ps[i][j + 1] += ps[i][j]; }
  }
  auto sum = [&](int i, int l, int r) -> int { return ps[i][r] - ps[i][l]; };

  vc<vi> indices(26);
  rep(i, 0, N) { indices[S[i] - 'a'].eb(i); }

  int ans = 0;
  rep(i, 0, N) {
    int j = S[i] - 'a';
    rep(k, 0, 26) {
      if (j == k) continue;
      auto it = upper_bound(all(indices[k]), i);
      if (it == indices[k].end()) continue;
      int l = *it;
      if (sum(j, i + 1, l) > 0 or sum(k, i + 1, l) > 0) continue;
      ans += 1;
    }
  }
  cout << ans;
}