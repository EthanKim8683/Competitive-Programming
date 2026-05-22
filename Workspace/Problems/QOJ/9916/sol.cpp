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
const int MOD = 998244353;

template <class T>
struct RMQ {
  vc<vc<T>> jmp;
  RMQ(const vc<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.eb(sz(V) - pw * 2 + 1);
      rep(j, 0, sz(jmp[k])) jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:54
  // thinking done: 6:14
  // target impl time: 25 min
  // initial impl done: 6:51

  // ub can only be delayed by at most K

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    int K;
    cin >> K;

    vi C(K + 1);
    rep(i, 1, K + 1) { cin >> C[i]; }

    int n = 0;
    rep(i, 0, N) { chmax(n, B[i] + A[i]); }

    vi A2(M + 1, -INF);
    rep(i, 0, N) { chmax(A2[B[i]], A[i]); }
    RMQ<int> rmq(A2);

    auto combine = [&](pii &a, pii b) -> void {
      if (b.fs < a.fs) {
        a = b;
      } else if (b.fs == a.fs) {
        (a.sd += b.sd) %= MOD;
      }
    };

    vc dp(n + K, vc<pii>(K + 1, {INF, 0}));
    dp[0][0] = {0, 1};
    pii ans = {INF, 0};
    rep(i, 0, n + K) {
      rep(j, 0, K + 1) {
        rep(k, 1, K + 1) {
          combine(i < M and rmq.query(i + 1, M + 1) != -INF
                      ? dp[i + k][max(
                            j, i + k + rmq.query(i + 1, min(i + k, M) + 1) - n)]
                  : i + k < n + j ? dp[i + k][j]
                                  : ans,
                  {dp[i][j].fs + C[k], dp[i][j].sd});
        }
      }
    }
    cout << ans.fs << ' ' << ans.sd << '\n';
  }
}
