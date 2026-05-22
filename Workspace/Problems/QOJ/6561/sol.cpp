#ifndef U
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

  // c1 + p1 * c2 < c2 + p2 * c1
  // (1 - p2) * c1 < (1 - p1) * c2
  // c1 / (1 - p1) < c2 / (1 - p2)

  int N;
  cin >> N;

  vc<tuple<double, double, int>> tests(N);
  for (auto &[c, p, d] : tests) {
    cin >> c >> p >> d;
    d--;
  }

  vc<vi> adj(N);
  rep(i, 0, N) {
    auto [c, p, d] = tests[i];
    if (d == -1) continue;
    adj[d].pb(i);
  }

  using T = tuple<double, double, int, int, int>;

  auto less = [](T a, T b) -> bool {
    auto [c1, p1, h1, l1, r1] = a;
    auto [c2, p2, h2, l2, r2] = b;
    return make_pair(c1 + p1 * c2, h1) > make_pair(c2 + p2 * c1, h2);
  };

  vi parent(N, -1);
  auto merge = [&](T a, T b) -> T {
    auto [c1, p1, h1, l1, r1] = a;
    auto [c2, p2, h2, l2, r2] = b;
    parent[l2] = r1;
    return {c1 + p1 * c2, p1 * p2, min(h1, h2), l1, r2};
  };

  auto dfs = [&](auto self, int a,
                 int h) -> priority_queue<T, vc<T>, decltype(less)> {
    priority_queue<T, vc<T>, decltype(less)> pq(less);
    for (auto b : adj[a]) {
      auto pq2 = self(self, b, h + 1);
      if (sz(pq) < sz(pq2)) {
        pq.swap(pq2);
      }
      while (sz(pq2) > 0) {
        pq.push(pq2.top());
        pq2.pop();
      }
    }

    auto [c, p, d] = tests[a];
    T top = {c, p, h, a, a};
    while (sz(pq) > 0 and less(top, pq.top())) {
      top = merge(top, pq.top());
      pq.pop();
    }
    pq.push(top);
    return pq;
  };
  priority_queue<T, vc<T>, decltype(less)> pq(less);
  rep(i, 0, N) {
    if (get<2>(tests[i]) != -1) continue;
    auto pq2 = dfs(dfs, i, 0);
    while (sz(pq2) > 0) {
      pq.push(pq2.top());
      pq2.pop();
    }
  }
  T accum = {0, 1, -1, -1, -1};
  while (sz(pq) > 0) {
    accum = merge(accum, pq.top());
    pq.pop();
  }

  vi ans;
  int a = get<4>(accum);
  while (a != -1) {
    ans.pb(a);
    a = parent[a];
  }
  reverse(all(ans));
  for (auto e : ans) {
    cout << e + 1 << '\n';
  }
}
