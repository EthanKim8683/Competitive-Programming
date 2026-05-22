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

  // start: 5:44
  // thinking done: 5:49
  // target impl time: 10 min
  // initial impl done: 6:04

  int N, M;
  cin >> N >> M;

  vi C(N);
  for (auto &e : C) cin >> e;

  vc<pii> ranges(M);
  for (auto &[s, e] : ranges) {
    cin >> s >> e;
    s--;
  }
  sort(all(ranges), [&](pii a, pii b) -> bool {
    auto key = [&](pii x) -> pii {
      auto [l, r] = x;
      return {l, -r};
    };
    return key(a) < key(b);
  });
  for (int i = M - 1; i - 1 >= 0; i--) {
    chmin(ranges[i - 1].sd, ranges[i].sd);
  }

  vi st(2 * (M + 1), INF);
  auto apply = [&](int i, int x) -> void {
    for (chmin(st[i += M + 1], x); i >>= 1;) {
      st[i] = min(st[i << 1], st[i << 1 | 1]);
    }
  };
  auto prod = [&](int l, int r) -> int {
    int rv = INF;
    for (l += M + 1, r += M + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        chmin(rv, st[l]);
        l++;
      }
      if (r & 1) {
        r--;
        chmin(rv, st[r]);
      }
    }
    return rv;
  };
  apply(0, 0);
  rep(i, 0, N) {
    int l = upper_bound(all(ranges), pii{INF, i},
                        [&](pii a, pii b) -> bool {
                          auto key = [&](pii x) -> pii {
                            auto [l, r] = x;
                            return {r, l};
                          };
                          return key(a) < key(b);
                        }) -
            ranges.begin(),
        r = upper_bound(all(ranges), pii{i, INF}) - ranges.begin();
    apply(r, prod(l, r) + C[i]);
  }
  cout << prod(M, M + 1) << '\n';
}
