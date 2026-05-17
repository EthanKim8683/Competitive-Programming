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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // min(sum of div 1s, sum of div 2s)
  //
  // contrib_div1 = x, x <= min(hard, med)
  // contrib_div2 = min(med - x, easy)
  //
  // med - x = easy
  // x = med - easy
  // greedy nonincreasing med - easy cuz too high x eats away at easy
  //
  // binary search?

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<tuple<int, int, int>> writers(N);
    for (auto &[a, b, c] : writers) {
      cin >> a >> b >> c;
    }

    auto check = [&](int x) -> bool {
      int div1 = 0, div2 = 0, ex = 0;
      for (auto [a, b, c] : writers) {
        int d = min(a, b);
        div1 += d;
        div2 += min(b - d, c);
        ex += max(d - max(b - c, 0ll), 0ll);
      }
      return div1 >= x and div2 + min(div1 - x, ex) >= x;
    };
    int l = 0, r = INF;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << l << '\n';
  }
}
