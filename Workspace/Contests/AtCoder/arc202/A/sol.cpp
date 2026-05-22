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

  // merge least to greatest
  //
  // implement with priority queue?

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    priority_queue<pii> pq;
    map<int, int> A2;
    auto insert = [&](int i, int x) -> void {
      pq.emplace(-x, i);
      A2.emplace(i, x);
    };
    rep(i, 0, N) { insert(i, A[i]); }
    int ans = 0;
    while (sz(pq) > 1) {
      auto [x1, i1] = pq.top();
      x1 = -x1;
      pq.pop();
      auto [x2, i2] = pq.top();
      x2 = -x2;
      if (x1 != x2 or next(A2.find(i2)) != A2.find(i1)) {
        auto it = A2.find(i1);
        int x3 = INF;
        if (it != A2.begin()) {
          chmin(x3, prev(it)->second);
        }
        if (next(it) != A2.end()) {
          chmin(x3, next(it)->second);
        }
        ans += x3 - x1;
        A2.erase(i1);
        insert(i1, x3);
      } else {
        pq.pop();
        A2.erase(i1);
        A2.erase(i2);
        insert(i1, x1 + 1);
      }
    }
    cout << ans << '\n';
  }
}
