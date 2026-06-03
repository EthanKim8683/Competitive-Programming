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

const int INF = 1e18;

template <typename K, typename V>
struct best {
  map<K, V> m;
  set<pair<V, K>> s;
  int th;

  best(int th) : th(th) {}

  void insert(K k, V v) {
    if (m.contains(k)) {
      s.erase({m[k], k});
    }
    m[k] = v;
    s.emplace(v, k);
    while (sz(m) > th) {
      auto it = prev(s.end());
      auto [v, k] = *it;
      m.erase(k);
      s.erase(it);
    }
  }

  int size() { return sz(m); }

  bool contains(K k) { return m.contains(k); }

  V operator[](K k) { return m[k]; }

  pair<K, V> top() {
    auto [v, k] = *s.begin();
    return {k, v};
  }

  void pop() {
    auto it = s.begin();
    auto [v, k] = *it;
    m.erase(k);
    s.erase(it);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, K;
  cin >> N >> M >> K;

  vc<vc<pii>> adj(N);
  rep(i, 0, M) {
    int x, y, w;
    cin >> x >> y >> w;
    x--, y--;
    adj[x].eb(w, y);
    adj[y].eb(w, x);
  }
  rep(i, 0, N) {
    sort(all(adj[i]));
    adj[i].resize(min(sz(adj[i]), K));
  }

  set<pii> seen;
  best<pii, int> pq(N + 2 * K);
  auto push = [&](int s, int t, int d) -> void {
    if (seen.contains({s, t})) return;
    if (pq.contains({s, t}) and d >= pq[{s, t}]) return;
    pq.insert({s, t}, d);
  };
  rep(i, 0, N) { push(i, i, 0); }
  int k = 0;
  while (sz(pq) > 0) {
    auto [st, d] = pq.top();
    seen.insert(st);
    pq.pop();
    k++;
    if (k == N + 2 * K) {
      cout << d << '\n';
      exit(0);
    }
    auto [s, t] = st;
    for (auto [w, b] : adj[t]) {
      push(s, b, d + w);
    }
  }
}
