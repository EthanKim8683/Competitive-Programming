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
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi deltas;
    deltas.pb(A[0]);
    rep(i, 0, N - 1) { deltas.pb((A[i + 1] + K - A[i]) % K); }
    deltas.pb((K - A[N - 1]) % K);

    priority_queue<int> pq;
    int resid = 0, ans = 0;
    for (auto e : deltas) {
      resid += e;
      ans += e;
      if (resid - K >= 0) {
        pq.push(-e);
        resid -= K;
        ans -= e;
      } else {
        if (sz(pq) > 0 and e > -pq.top()) {
          ans += -pq.top();
          pq.pop();
          ans -= e;
          pq.push(-e);
        }
      }
    }
    cout << ans << '\n';
  }
}
