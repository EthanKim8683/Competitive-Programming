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

  int T;
  cin >> T;

  while (T--) {
    int N, K, P, M;
    cin >> N >> K >> P >> M;
    P--;

    vi A(N);
    for (auto &e : A) cin >> e;

    // K - 1 at most that we never play

    priority_queue<pii> pq;
    queue<int> q;
    rep(i, 0, N) { q.push(i); }
    int ans = 0, sum = 0;
    while (true) {
      while (sz(pq) < K) {
        int i = q.front();
        q.pop();
        pq.emplace(i == P ? INF : -A[i], i);
      }
      int i = pq.top().sd;
      pq.pop();
      q.push(i);
      if (sum + A[i] > M) break;
      sum += A[i];
      if (i == P) {
        ans += 1;
      }
    }
    cout << ans << '\n';
  }
}
