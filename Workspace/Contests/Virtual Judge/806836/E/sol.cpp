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

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vc<pii> queries(Q);
    for (auto &[l, r] : queries) {
      cin >> l >> r;
      l--;
    }
    sort(all(queries), [&](pii a, pii b) -> bool {
      auto key = [&](pii x) -> pii { return {x.fs, -x.sd}; };
      return key(a) < key(b);
    });

    auto query = [&](int l, int r) -> int {
      cout << "? " << l + 1 << ' ' << r << endl;
      int rv;
      cin >> rv;
      return rv;
    };

    auto answer = [&](int x) -> void { cout << "! " << x << endl; };

    int l = (N - 1) / 2, r = N / 2 + 1;
    while (query(l, r) == 0) {
      l--;
      r++;
    }
    int m;
    if (r - l == 1) {
      m = l;
    } else {
      if (query(l, l + 1) == 0) {
        m = r - 1;
      } else {
        m = l;
      }
    }

    int ans = 0, rmax = 0;
    for (auto [l, r] : queries) {
      if (r <= rmax) continue;
      if (l <= m and m < r) {
        chmax(ans, query(l, r));
      }
      rmax = r;
    }
    answer(ans);
  }
}
