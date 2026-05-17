#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/dsu.hpp"
using namespace atcoder;

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

  // if can't beat each other, part of the same group
  //
  // if a group completely beats one, it can't be last person
  //
  // we need to find groups
  //
  // process increasing x, if there is ge y or ge z, group them

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<array<int, 3>> people(N);
    for (auto &[x, y, z] : people) {
      cin >> x >> y >> z;
      x--, y--, z--;
    }

    dsu d(N);
    auto use_perm = [&](array<int, 3> p) -> void {
      vi order(N);
      iota(all(order), 0);
      sort(all(order), [&](int a, int b) -> bool {
        return people[a][p[0]] < people[b][p[0]];
      });
      vc<pii> best(3, {-1, -1});
      for (auto e : order) {
        rep(i, 0, 3) {
          if (people[e][i] > best[i].fs) {
            best[i] = {people[e][i], e};
          } else {
            d.merge(best[i].sd, e);
          }
        }
      }
    };
    use_perm({0, 1, 2});
    use_perm({1, 0, 2});
    use_perm({2, 0, 1});
    pii best = {-1, -1};
    rep(i, 0, N) {
      if (i != d.leader(i)) continue;
      chmax(best, pii{people[i][0], d.size(i)});
    }
    cout << best.sd << '\n';
  }
}
