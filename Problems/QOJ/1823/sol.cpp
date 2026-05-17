#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

// #define int long long
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

const int MAXA = 1e9;

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

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, S, Q;
  if (argc > 1) {
    N = 1e5;
    S = 5;
    Q = 2e5;
  } else {
    cin >> N >> S >> Q;
  }

  vi P(N);
  if (argc > 1) {
    iota(all(P), 1);
  } else {
    for (auto &e : P) cin >> e;
  }

  vc<pii> queries(Q);
  if (argc > 1) {
    for (auto &[k, a] : queries) {
      k = rng() % N + 1;
      a = rng() % MAXA + 1;
    }
  } else {
    for (auto &[k, a] : queries) {
      cin >> k >> a;
    }
  }

  vi index(N + 1);
  rep(i, 0, N) { index[P[i]] = i; }

  vi right(N + 1);
  map<int, int> by_index;
  rep(i, 1, N + 1) {
    auto it = by_index.upper_bound(index[i]);
    if (it == by_index.end()) {
      right[i] = -1;
    } else {
      right[i] = it->second;
    }
    by_index.emplace(index[i], i);
  }

  int sum = 0;
  vi P2;
  auto dfs = [&](auto self, int p, int s) -> void {
    if (s == 1) {
      P2.pb(p);
      sum += p;
      return;
    }
    list<int> l;
    vc<list<int>::iterator> its(p + 1);
    rep(i, 1, p + 1) {
      if (right[i] == -1) {
        its[i] = l.insert(l.end(), i);
      } else {
        its[i] = l.insert(its[right[i]], i);
      }
    }
    for (auto e : l) {
      if (sum > MAXA) break;
      self(self, e, s - 1);
    }
  };
  dfs(dfs, N, S);

  vi ans(Q);

  vi order(Q);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool {
    auto key = [&](int x) -> int { return queries[x].sd; };
    return key(a) < key(b);
  });

  vc<vc<tuple<int, int, int>>> by_p2(N + 1);
  FT ft(N + 1);
  int ps = 0, j = 0;
  rep(i, 0, sz(P2)) {
    for (; j < Q; j++) {
      auto [k, a] = queries[order[j]];
      if (ps + P2[i] <= a) break;
      by_p2[P2[i]].eb(i - ft.query(k), a - ps, order[j]);
    }
    ps += P2[i];
    ft.update(P2[i], 1);
  }
  for (; j < Q; j++) {
    auto [k, a] = queries[order[j]];
    ans[order[j]] = sz(P2) - ft.query(k);
  }

  FT ft2(N);
  rep(i, 1, N + 1) {
    ft2.update(index[i], 1);
    for (auto [b, da, j] : by_p2[i]) {
      auto [k, a] = queries[j];
      if (k <= i and ft2.query(index[k]) < da) {
        ans[j] = b + 1;
      } else {
        ans[j] = b;
      }
    }
  }

  for (auto e : ans) {
    cout << e << '\n';
  }
}
