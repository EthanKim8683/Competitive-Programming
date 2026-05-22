#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

const int MAXM = 500;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<pair<double, double>> vertices(N);
  for (auto &[x, y] : vertices) {
    cin >> x >> y;
  }

  vc<vi> by_x(2 * MAXM), by_y(2 * MAXM);
  rep(i, 0, N) {
    auto [x1, y1] = vertices[i];
    auto [x2, y2] = vertices[(i + 1) % N];
    rep(j, ceil(min(x1, x2)), floor(max(x1, x2)) + 1) {
      by_x[MAXM + j].pb(floor((j - x1) * (y2 - y1) / (x2 - x1) + y1));
    }
    rep(j, ceil(min(y1, y2)), floor(max(y1, y2)) + 1) {
      by_y[MAXM + j].pb(floor((j - y1) * (x2 - x1) / (y2 - y1) + x1));
    }
  }
  vi ans;
  for (auto r : by_x) {
    assert(sz(r) % 2 == 0);
    sort(all(r));
    for (int i = 0; i < sz(r); i += 2) {
      ans.pb(r[i]);
    }
  }
  for (auto r : by_y) {
    assert(sz(r) % 2 == 0);
    sort(all(r));
    for (int i = 1; i < sz(r); i += 2) {
      ans.pb(r[i]);
    }
  }
  cout << sz(ans) << '\n';
  for (auto e : ans) {
    cout << e << '\n';
  }
}
