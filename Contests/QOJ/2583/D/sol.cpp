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

const int INF = 1e18;

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
    if (a == b) return -INF;
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};
int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  vc<map<int, int>> adj;
#ifdef ETHANKIM8683
  mt19937 $rng(atoi(argv[1]));

  N = 1000;

  adj.resize(N);
  rep(i, 1, N) {
    int b = $rng() % i, d = $rng() % (int) 1e7 + 1;
    adj[i][b] = adj[b][i] = d;
  }
  int $a, $b, $d = $rng() % (int) 1e7 + 1;
  do {
    $a = $rng() % N;
    $b = $rng() % N;
  } while ($a == $b or adj[$a].contains($b));
  adj[$a][$b] = adj[$b][$a] = $d;

  auto $adj = adj;
#else
  cin >> N;

  adj.resize(N);
  rep(i, 0, N) {
    int a, b, d;
    cin >> a >> b >> d;
    a--, b--;
    adj[a][b] = adj[b][a] = d;
  }
#endif

  vc<pii> cycle;
  vc<bool> seen(N, false);
  auto dfs1 = [&](auto self, int a, int p) -> int {
    seen[a] = true;

    for (auto [b, w] : adj[a]) {
      if (b == p) continue;

      int r = -1;
      if (seen[b]) {
        r = b;
      } else {
        r = self(self, b, a);
      }

      if (r != -1) {
        cycle.eb(a, w);
        adj[a].erase(b);
        adj[b].erase(a);

        if (r == a) return -1;
        return r;
      }
    }
    return -1;
  };
  dfs1(dfs1, 0, -1);
  reverse(all(cycle));

  vi ans(N, -INF);
  for (auto [e, w] : cycle) {
    pii furthest = {-INF, -1};
    auto dfs2 = [&](auto self, int a, int p, int d) -> void {
      seen[a] = true;

      chmax(furthest, pii{d, a});

      for (auto [b, w] : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + w);
      }
    };
    dfs2(dfs2, e, -1, 0);
    int d1 = furthest.sd;
    dfs2(dfs2, d1, -1, 0);
    int d2 = furthest.sd;

    auto dfs3 = [&](auto self, int a, int p, int d) -> void {
      chmax(ans[a], d);

      for (auto [b, w] : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + w);
      }
    };
    dfs3(dfs3, d1, -1, 0);
    dfs3(dfs3, d2, -1, 0);
  }

  vi furthest(N, -INF);
  for (auto [e, w] : cycle) {
    auto dfs4 = [&](auto self, int a, int p, int d) -> void {
      chmax(furthest[e], d);

      for (auto [b, w] : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + w);
      }
    };
    dfs4(dfs4, e, -1, 0);
  }

  int M = sz(cycle);

  vc<pii> cycle3;
  cycle3.insert(cycle3.end(), all(cycle));
  cycle3.insert(cycle3.end(), all(cycle));
  cycle3.insert(cycle3.end(), all(cycle));

  vi ps(3 * M + 1);
  ps[0] = 0;
  rep(i, 0, 3 * M) { ps[i + 1] = ps[i] + cycle3[i].sd; }

  vi value1(3 * M), value2(3 * M);
  rep(i, 0, 3 * M) {
    auto [e, w] = cycle3[i];
    value1[i] = furthest[e] - ps[i];
    value2[i] = furthest[e] + ps[i];
  }
  RMQ<int> rmq1(value1), rmq2(value2);

  int j = 0, k = 0;
  rep(i, 0, 3 * M) {
    auto [e, w] = cycle3[i];

    while (ps[i] - ps[j] > ps[M] / 2) {
      j++;
    }
    while (k < 3 * M and ps[k] - ps[i] <= ps[M] / 2) {
      k++;
    }

    if (M <= i and i < 2 * M) {
      int furthest = -INF;
      chmax(furthest, rmq1.query(j, i) + ps[i]);
      chmax(furthest, rmq2.query(i + 1, k) - ps[i]);

      auto dfs5 = [&](auto self, int a, int p, int d) -> void {
        chmax(ans[a], d + furthest);

        for (auto [b, w] : adj[a]) {
          if (b == p) continue;
          self(self, b, a, d + w);
        }
      };
      dfs5(dfs5, e, -1, 0);
    }
  }

#ifdef ETHANKIM8683
  rep(i, 0, N) {
    vi dist(N, INF);
    priority_queue<pii> pq;
    auto push = [&](int a, int d) -> void {
      if (d >= dist[a]) return;
      dist[a] = d;
      pq.emplace(-d, a);
    };

    push(i, 0);
    while (sz(pq) > 0) {
      auto [d, a] = pq.top();
      pq.pop();
      if ((d = -d) != dist[a]) continue;

      for (auto [b, w] : $adj[a]) {
        push(b, d + w);
      }
    }

    assert(ans[i] == *max_element(all(dist)));
  }
#else
  for (auto e : ans) {
    cout << e << ' ';
  }
#endif
}
