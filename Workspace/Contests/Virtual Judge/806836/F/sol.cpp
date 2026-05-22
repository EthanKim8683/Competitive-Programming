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

  int N;
  cin >> N;

  auto attempt = [&](vi D) -> int {
    for (auto e : D) {
      cout << e << ' ';
    }
    cout << endl;
    int rv;
    cin >> rv;
    if (rv == 0) {
      exit(0);
    }
    return rv;
  };

  vc<bool> solved(N, false);
  vi ans(N, N);
  int d = attempt(ans);
  rep(i, 0, N) {
    ans[i] = 1;
    int d1 = attempt(ans);
    if (d1 > d) {
      ans[i] = 1 + d1;
      solved[i] = true;
      continue;
    }
    ans[i] = 2 * N;
    int d2 = attempt(ans);
    if (d2 > d) {
      ans[i] = 2 * N - d2;
      solved[i] = true;
      continue;
    }
    ans[i] = N;
  }
  rep(i, 0, N) {
    if (solved[i]) continue;
    ans[i] = 1;
    int d1 = attempt(ans);
    if (d1 > 1) {
      ans[i] = 1 + d1;
      continue;
    }
    ans[i] = 2 * N;
    int d2 = attempt(ans);
    if (d2 > 1) {
      ans[i] = 2 * N - d2;
      continue;
    }
    ans[i] = N;
  }
  attempt(ans);
}
