#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

  int N, W;
  cin >> N >> W;

  vc<tuple<int, int, int>> intervals(N);
  for (auto &[x, ylow, yhigh] : intervals) {
    cin >> x >> ylow >> yhigh;
  }

  vc<pii> points(2 * N);
  rep(i, 0, N) {
    auto [x, ylow, yhigh] = intervals[i];
    points[2 * i] = {x, ylow};
    points[2 * i + 1] = {x, yhigh};
  }

  auto less = [&](pii a, pii b) -> bool {
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    if (x1 * y2 == x2 * y1) return false;
    return (x1 * y2 < x2 * y1) ^ (y1 < 0) ^ (y2 < 0);
  };

  auto reciprocal = [&](pii x) -> pii { return {x.sd, x.fs}; };

  vi order(2 * N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool {
    return less(reciprocal(points[a]), reciprocal(points[b]));
  });
  vi index(2 * N);
  rep(i, 0, 2 * N) { index[order[i]] = i; }
  auto swap2 = [&](int a, int b) -> void {
    int i = index[a], j = index[b];
    swap(index[a], index[b]);
    swap(order[i], order[j]);
  };

  auto does_intersect = [&](int a, int b) -> bool {
    return points[a].sd != points[b].sd;
  };

  auto intersect = [&](int a, int b) -> pii {
    auto [x1, y1] = points[a];
    auto [x2, y2] = points[b];
    return {y1 * x2 - y2 * x1, y1 - y2};
  };

  auto less2 = [&](tuple<pii, int, int> a, tuple<pii, int, int> b) -> bool {
    return less(get<0>(a), get<0>(b));
  };
  priority_queue<tuple<pii, int, int>, vc<tuple<pii, int, int>>,
                 decltype(less2)>
      pq(less2);
  set<pii> pushed;
  pii t0 = {0, 1};
  auto push = [&](int a, int b) -> void {
    if (index[b] - index[a] != 1) return;

    if (pushed.contains({a, b}) or pushed.contains({b, a})) return;
    pushed.insert({a, b});

    if (!does_intersect(a, b)) return;
    auto t = intersect(a, b);
    if (less(t0, t)) return;

    pq.emplace(t, a, b);
  };
  auto nudge = [&](int a, int b0) -> void {
    if (index[a] - 1 >= 0) {
      push(order[index[a] - 1], a);
    }
    if (index[a] + 1 < 2 * N) {
      push(a, order[index[a] + 1]);
    }
  };

  vi ps(2 * N, 0);
  rep(i, 0, N) {
    ps[index[2 * i]] += 1;
    ps[index[2 * i + 1]] -= 1;
  }
  rep(i, 0, 2 * N - 1) { ps[i + 1] += ps[i]; }
  int holes = 0;
  rep(i, 0, 2 * N - 1) {
    if (ps[i] != 0) continue;
    holes++;
  }
  auto add = [&](int i, int x) -> void {
    if (ps[i] == 0) {
      holes--;
    }
    ps[i] += x;
    if (ps[i] == 0) {
      holes++;
    }
  };

  auto value = [&](pii t) -> double { return (double) t.fs / t.sd; };

  auto sign = [&](int x) -> int { return (x > 0) - (x < 0); };

  double ans = 0;
  rep(i, 0, 2 * N) { nudge(i, -1); }
  while (sz(pq) > 0) {
    auto [t, a, b] = pq.top();
    pq.pop();
    assert(index[b] - index[a] == 1);

    if (holes == 0) {
      ans += value(t0) - value(t);
    }
    t0 = t;

    int i = index[a];

    auto [x1, y1] = points[a];
    auto [x2, y2] = points[b];
    if (x1 > x2) {
      swap(a, b);
      swap(x1, x2);
      swap(y1, y2);
    }

    int e1 = sign(points[a ^ 1].sd - y1) * sign(y1),
        e2 = sign(points[b ^ 1].sd - y2) * sign(y2);
    if (e1 > e2) {
      add(i, 2);
    } else if (e1 < e2) {
      add(i, -2);
    }

    swap2(a, b);
    nudge(a, b);
    nudge(b, a);
  }

  vi Y;
  for (auto [x, ylow, yhigh] : intervals) {
    Y.pb(ylow);
    Y.pb(yhigh);
  }
  sort(all(Y));
  Y.erase(unique(all(Y)), Y.end());
  vi ps2(2 * N, 0);
  for (auto [x, ylow, yhigh] : intervals) {
    int l = lower_bound(all(Y), ylow) - Y.begin(),
        r = lower_bound(all(Y), yhigh) - Y.begin();
    ps2[l]++;
    ps2[r]--;
  }
  rep(i, 0, 2 * N - 1) { ps2[i + 1] += ps2[i]; }
  int holes2 = 0;
  rep(i, 0, 2 * N - 1) {
    if (ps2[i] != 0) continue;
    holes2++;
  }
  if (holes2 == 0) {
    cout << -1;
    exit(0);
  }

  cout << setprecision(12) << fixed << ans;
}
