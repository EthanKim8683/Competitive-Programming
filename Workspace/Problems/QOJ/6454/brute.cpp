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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // k = (ps + ceil(-psmin / 2) * 2) / 2 + ceil(-psmin / 2) * 2
  //   = ps / 2 + ceil(-psmin / 2) * 2
  // K > k
  //
  // psmin, ps, cost

  // given psmin, find min cost to get k > K

  int N, K;
  cin >> N >> K;

  string S;
  cin >> S;

  vi C(N);
  for (auto &e : C) cin >> e;

  if (N % 2 == 1) {
    int ans = 0;
    for (auto e : C) {
      if (e > 0) continue;
      ans += e;
    }
    cout << ans << '\n';
    exit(0);
  }

  int ans = INF;
  rep(i, 0, N + 1) {
    priority_queue<int> pq;
    int psmin = 0;
    rep(j, 0, i) {
      if (S[j] == '(') {
        psmin += 1;
        pq.push(-C[j]);
      } else {
        psmin -= 1;
      }
    }
    int ps = psmin;
    rep(j, i, N) {
      if (S[j] == '(') {
        ps += 1;
      } else {
        ps -= 1;
        pq.push(-C[j]);
      }
    }
    int k = ps / 2 - psmin;
    if (i % 2 == 1) {
      k += 1;
    }
    int cost = 0;
    while (k <= K and sz(pq) > 0) {
      k += 1;
      cost += -pq.top();
      pq.pop();
    }
    if (k > K) {
      chmin(ans, cost);
    }
  }
  if (ans == INF) {
    cout << "?\n";
  } else {
    cout << ans << '\n';
  }
}
