#pragma GCC optimize("Ofast,unroll-loops")
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
    if (a == b) return INF;
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:27
  // thinking done: 6:13
  // target impl time: 20 min
  // initial impl done: 6:25

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<pii> robots(N);
    for (auto &[x, y] : robots) {
      cin >> x >> y;
    }

    vi X;
    X.pb(0);
    for (auto [x, y] : robots) {
      X.pb(x - 1);
      X.pb(x);
      X.pb(x + 1);
    }
    sort(all(X));
    X.erase(unique(all(X)), X.end());

    vi Ymin(sz(X), INF), Ymax(sz(X), -INF);
    for (auto [x, y] : robots) {
      x = lower_bound(all(X), x) - X.begin();
      chmin(Ymin[x], y);
      chmax(Ymax[x], y);
    }

    vi Ypmin(sz(X)), Ysmax(sz(X));
    Ypmin[0] = 0;
    rep(i, 0, sz(X) - 1) { Ypmin[i + 1] = min(Ypmin[i], Ymin[i]); }
    Ysmax.back() = 0;
    for (int i = sz(X) - 1; i >= 1; i--) {
      Ysmax[i - 1] = max(Ysmax[i], Ymax[i]);
    }

    for (auto e : Ypmin) {
      cerr << e << ' ';
    }
    cerr << '\n';

    int cost1 = INF, cost2 = INF, cost3 = INF, cost4 = INF;
    rep(i, 0, sz(X)) {
      int x = X[i], y = Ysmax[i];
      if (x < 0) continue;
      chmin(cost1, x + y);
      chmin(cost2, x + 2 * y);
      chmin(cost3, 2 * x + y);
      chmin(cost4, 2 * x + 2 * y);
    }

    int ans = INF;
    rep(i, 0, sz(X)) {
      int x = -X[i], y = -Ypmin[i];
      if (x < 0) continue;
      chmin(ans, cost1 + 2 * x + 2 * y);
      chmin(ans, cost2 + 2 * x + y);
      chmin(ans, cost3 + x + 2 * y);
      chmin(ans, cost4 + x + y);
    }

    cout << ans << '\n';
  }
}
