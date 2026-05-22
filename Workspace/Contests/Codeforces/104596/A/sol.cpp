#include <iomanip>
#include <queue>
#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, p;
  cin >> n >> m >> p;
  vi xj(n), yj(n);
  rep(i, 0, n) cin >> xj[i] >> yj[i];
  vi xt(m), yt(m);
  rep(i, 0, m) cin >> xt[i] >> yt[i];
  vi xf(p), yf(p);
  rep(i, 0, p) cin >> xf[i] >> yf[i];

  auto solve = [&](vi const &x, vi const &y) -> double {
    int q = sz(x);
    using U = pair<int, pii>;
    priority_queue<U, vc<U>, greater<>> pq;
    rep(i, 0, n) {
      rep(j, 0, q) {
        int dist =
            (x[j] - xj[i]) * (x[j] - xj[i]) + (y[j] - yj[i]) * (y[j] - yj[i]);

        pq.push({dist, {i, j}});
      }
    }

    long double sum = 0.0;
    vc<bool> a(n), b(q);
    while (!pq.empty()) {
      auto top = pq.top();
      pq.pop();
      if (a[top.sd.fs] || b[top.sd.sd]) continue;
      a[top.sd.fs] = true;
      b[top.sd.sd] = true;

      sum += sqrt(top.fs);
    }

    return sum;
  };

  long double u = solve(xt, yt);
  long double v = solve(xf, yf);

  long double ans = u + v;
  cout << fixed << setprecision(8) << ans << endl;
}