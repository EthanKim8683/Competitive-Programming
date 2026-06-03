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

  // consider each strongest a chosen one already
  //
  // now it's number of chosen ones

  int N, M, K;
  cin >> N >> M >> K;

  vi P(N);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  vi S(N);
  for (auto &e : S) {
    cin >> e;
    e--;
  }

  set<int> chosen;
  rep(i, 0, K) {
    int e;
    cin >> e;
    e--;
    chosen.insert(e);
  }

  vc<vi> by_school(M);
  rep(i, 0, N) { by_school[S[i]].pb(i); }
  rep(i, 0, M) {
    if (by_school[i].empty()) continue;
    sort(all(by_school[i]), [&](int a, int b) -> bool { return P[a] > P[b]; });
    chosen.insert(by_school[i][0]);
  }
  cout << sz(chosen) - M << '\n';
}
