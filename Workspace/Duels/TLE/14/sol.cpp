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

  auto query = [&](int x, int y) -> string {
    cout << x << ' ' << y << endl;
    string color;
    cin >> color;
    return color;
  };

  string color0 = query(0, 0);
  int l = 0, r = 1 << 29;
  rep(i, 1, N) {
    int m = l + (r - l) / 2;
    if (query(m, m) == color0) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << ' ' << l + 1 << ' ' << l + 1 << ' ' << l << '\n';
}
