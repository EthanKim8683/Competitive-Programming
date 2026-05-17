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

  // r+c=same value -> S[r][c]=same value

  int N;
  cin >> N;

  vc<string> S(N);
  for (auto &e : S) cin >> e;

  vc<char> by_x(2 * N - 1, '\0');
  bool ok = true;
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (S[i][j] == '?') continue;
      if (by_x[i + j] == '\0') {
        by_x[i + j] = S[i][j];
      }
      ok = ok and by_x[i + j] == S[i][j];
    }
  }
  if (!ok) {
    cout << "-1\n";
    exit(0);
  }

  for (auto &e : by_x) {
    if (e != '\0') continue;
    e = '0';
  }

  rep(i, 0, N) {
    rep(j, 0, N) { cout << by_x[i + j]; }
    cout << '\n';
  }
}
