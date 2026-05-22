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

struct FT {
  vi s;
  FT(int n) : s(n) {}
  void update(int pos, int dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  int query(int pos) {
    int res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(int sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
    return pos;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 11:51
  // thinking done: 12:05
  // target impl time: 35 min
  // initial impl done: 12:38

  int N, Q;
  cin >> N >> Q;

  vc<vi> adj(N);
  int r;
  rep(i, 0, N) {
    int p;
    cin >> p;
    p--;
    if (p == -1) {
      r = i;
    } else {
      adj[p].pb(i);
    }
  }

  vi K(Q);
  for (auto &e : K) {
    cin >> e;
    e--;
  }

  vi tin(N), tout(N);
  int t = 0;
  auto dfs = [&](auto self, int a) -> void {
    tin[a] = t;
    t++;
    for (auto b : adj[a]) {
      self(self, b);
    }
    tout[a] = t;
  };
  dfs(dfs, r);

  auto get_size = [&](int a) -> int { return tout[a] - tin[a]; };

  vc<array<int, 3>> ans(Q);

  int sum = 0;
  vi sums(N);
  auto dfs2 = [&](auto self, int a) -> void {
    sum += get_size(a);
    sums[a] = sum;
    for (auto b : adj[a]) {
      sum -= get_size(b);
      self(self, b);
      sum += get_size(b);
    }
    sum -= get_size(a);
  };
  dfs2(dfs2, r);

  vi ps(N + 1);
  ps[0] = 0;
  rep(i, 0, N) { ps[i + 1] = ps[i] + sums[i]; }

  rep(i, 0, Q) { ans[i][0] = upper_bound(all(ps), K[i]) - ps.begin() - 1; }

  vc<vi> by_x(N);
  rep(i, 0, Q) { by_x[ans[i][0]].pb(i); }

  vc<vi> st(2 * N);
  rep(i, 0, N) { st[tin[i] + N].pb(i); }
  for (int i = N - 1; i >= 1; i--) {
    merge(all(st[i << 1]), all(st[i << 1 | 1]), back_inserter(st[i]));
  }
  auto get_less = [&](int l, int r, int x) -> int {
    int rv = 0;
    auto use = [&](int i) -> void {
      rv += lower_bound(all(st[i]), x) - st[i].begin();
    };
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) use(l++);
      if (r & 1) use(--r);
    }
    return rv;
  };

  vc<array<int, 4>> ranges(N);
  FT ft(N);
  auto dfs3 = [&](auto self, int a) -> void {
    ranges[a] = {tin[a], tout[a], tout[a], tout[a]};
    ft.update(a, get_size(a));

    for (auto e : by_x[a]) {
      int k = K[e];
      k -= ps[ans[e][0]];

      int z = ft.lower_bound(k + 1);
      ans[e][1] = z;
      k -= ft.query(z);

      auto [l1, r1, l2, r2] = ranges[z];
      auto check = [&](int y) -> bool {
        return get_less(l1, r1, y) + get_less(l2, r2, y) <= k;
      };
      int l = 0, r = N;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        check(m) ? l = m : r = m - 1;
      }
      ans[e][2] = l;
    }

    for (auto b : adj[a]) {
      ranges[a] = {tin[a], tin[b], tout[b], tout[a]};
      ft.update(a, -get_size(b));
      self(self, b);
      ft.update(a, get_size(b));
    }
    ft.update(a, -get_size(a));
  };
  dfs3(dfs3, r);

  for (auto [x, z, y] : ans) {
    cout << x * N * N + z * N + y << '\n';
  }
}
