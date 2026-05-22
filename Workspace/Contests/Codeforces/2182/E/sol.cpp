#ifndef L
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
    int N, M, K;
    cin >> N >> M >> K;

    vi A(M);
    for (auto &e : A) cin >> e;

    vc<tuple<int, int, int>> friends(N);
    for (auto &[x, y, z] : friends) {
      cin >> x >> y >> z;
    }

    int total1 = 0;
    for (auto [x, y, z] : friends) {
      total1 += y;
    }

    sort(all(A));
    sort(all(friends));
    reverse(all(friends));
    int ans = 0, total2 = 0;
    multiset<int> costs1, costs2;
    for (auto [x, y, z] : friends) {
      int boxes = A.end() - lower_bound(all(A), x) - total2;
      costs2.insert(z - y);
      if (boxes == 0) {
        auto it1 = costs2.begin();
        if (total1 + *it1 > K) {
          if (sz(costs1) >= 1) {
            auto it2 = prev(costs1.end());
            if (*it2 > *it1) {
              total1 -= *it2;
              costs1.erase(it2);
              total1 += *it1;
              costs1.insert(*it1);
              costs2.erase(it1);
            }
          }
        } else {
          ans += 1;
          total1 += *it1;
          costs1.insert(*it1);
          costs2.erase(it1);
        }
      } else {
        ans += 1;
        total2 += 1;
      }
    }
    cout << ans << '\n';
  }
}
