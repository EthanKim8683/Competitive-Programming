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

const int INF = 1e18;

template <class T>
struct RMQ {
  vc<vc<T>> jmp;
  RMQ(const vc<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.eb(sz(V) - pw * 2 + 1);
      rep(j, 0, sz(jmp[k])) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    a = clamp(a, 0ll, sz(jmp[0]));
    b = clamp(b, a, sz(jmp[0]));
    if (a == b) return INF;
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:56
  // thinking done: 6:02
  // target impl time: 20 min
  // initial impl done: 6:17

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    string S;
    cin >> S;

    int c = 0;
    rep(i, 0, N) {
      if (S[i] == '1') {
        c += A[i];
      }
    }

    auto f = [&](int i) -> int { return S[i] == '1' ? 0 : A[i]; };

    vi cost1(N + 2);
    {
      cost1[0] = 0;
      priority_queue<pii> pq;
      pq.emplace(-cost1[0], K);
      rep(i, 1, N + 1) {
        while (i > pq.top().second) {
          pq.pop();
        }
        cost1[i] = -pq.top().first + f(i - 1);
        pq.emplace(-cost1[i], i + K);
      }
    }
    vi cost2(N + 2);
    {
      cost2[N + 1] = 0;
      priority_queue<pii> pq;
      pq.emplace(-cost2[N + 1], N + 1 - K);
      for (int i = N; i >= 1; i--) {
        while (i < pq.top().second) {
          pq.pop();
        }
        cost2[i] = -pq.top().first + f(i - 1);
        pq.emplace(-cost2[i], i - K);
      }
    }

    RMQ rmq1(cost1), rmq2(cost2);
    int base = c + rmq1.query(N + 1 - K, N + 1);

    int Q;
    cin >> Q;

    while (Q--) {
      int p, v;
      cin >> p >> v;

      if (S[p - 1] == '1') {
        cout << base + v - A[p - 1] << '\n';
      } else {
        int ans = INF;
        chmin(ans, c + rmq1.query(N + 1 - K, p));
        chmin(ans, c + rmq2.query(p + 1, K + 1));
        chmin(ans, c + rmq1.query(p - K, p) + v + rmq2.query(p + 1, p + K + 1));
        rep(i, max(p - K + 1, 1ll), min(p, N + 1)) {
          chmin(ans, c + rmq1.query(i - K, i) + f(i - 1) +
                         rmq2.query(p + 1, i + K + 1));
        }
        rep(i, max(p + 1, 1ll), min(p + K, N + 1)) {
          chmin(ans, c + rmq1.query(i - K, p) + f(i - 1) +
                         rmq2.query(i + 1, i + K + 1));
        }
        cout << ans << '\n';
      }
    }
  }
}
