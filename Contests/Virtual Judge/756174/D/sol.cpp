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
typedef tuple<vector<int>, int, int> seg;

const int INF = 1e9;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // if it can be at least 2nd max and other half has any less

  int N, K;
  cin >> N >> K;

  int M = 1 << N;

  vi A(M);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  vi index(M);
  rep(i, 0, M) { index[A[i]] = i; }

  vc<vi> st(2 * M);
  rep(i, 0, M) { st[i + M].pb(A[i]); }
  for (int i = M - 1; i >= 1; i--) {
    merge(all(st[i << 1]), all(st[i << 1 | 1]), back_inserter(st[i]));
  }

  vi ans(M, N);
  rep(i, 1, 2 * M) {
    rep(j, 0, sz(st[i])) {
      int gt = sz(st[i]) - 1 - j, lt = min(st[i][j] - j, K);
      if (gt > lt) {
        int k = index[st[i][j]];
        ans[k] = min(ans[k], __lg(sz(st[i])) - 1);
      }
    }
  }
  for (auto e : ans) {
    cout << e << ' ';
  }
}