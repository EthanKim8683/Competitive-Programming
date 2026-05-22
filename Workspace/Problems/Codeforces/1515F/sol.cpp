#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if defined(ETHANKIM8683) and true
  mt19937 rng(time(nullptr));

  int N = 3e5, M = 3e5, X = rng() % (int) 1e9 + 1;

  vector<int> A(N);
  i64 _sum = 0;
  for (auto &e : A) {
    e = rng() % (int) 1e9 + 1;
    _sum += e;
  }
  while (_sum < (i64) X * (N - 1)) {
    int i = rng() % N, d = rng() % ((int) 1e9 - A[i] + 1);
    A[i] += d;
    _sum += d;
  }

  vector<pair<int, int>> edges(M);
  set<pair<int, int>> _seen;
  for (int i = 0; i < M; i++) {
    auto &[x, y] = edges[i];
    if (i < N - 1) {
      x = rng() % (i + 1);
      y = i + 1;
    } else {
      do {
        x = rng() % N;
        y = rng() % N;
        if (x > y) {
          swap(x, y);
        }
      } while (x == y or _seen.contains({x, y}));
    }
    _seen.insert({x, y});
  }
#else
  int N, M, X;
  cin >> N >> M >> X;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<pair<int, int>> edges(M);
  for (auto &[x, y] : edges) {
    cin >> x >> y;
    x--, y--;
  }
#endif

  vector<vector<pair<int, int>>> adj(N);
  for (int i = 0; i < M; i++) {
    auto [a, b] = edges[i];
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }

  if (accumulate(A.begin(), A.end(), 0ll) < (i64) X * (N - 1)) {
    cout << "NO";
    exit(0);
  }

  vector<set<int>> merges(N);
  dsu ds(N);
  for (int i = 0; i < M; i++) {
    auto [a, b] = edges[i];
    if (ds.same(a, b)) continue;
    ds.merge(a, b);
    merges[a].insert(i);
    merges[b].insert(i);
  }

  vector<i64> give(A.begin(), A.end());
  ds = dsu(N);
  auto merge = [&](int a, int b) -> int {
    a = ds.leader(a);
    b = ds.leader(b);
    if (ds.merge(a, b) == b) {
      swap(a, b);
    }
    if (merges[a].size() < merges[b].size()) {
      merges[a].swap(merges[b]);
    }
    for (auto i : merges[b]) {
      merges[a].insert(i);
    }
    merges[b].clear();
    give[a] += give[b];
    return a;
  };

  vector<i64> take(M, 0);
  queue<int> q;
  auto flow = [&](int a) -> void {
    a = ds.leader(a);
    if (merges[a].size() > 0) {
      int j = *merges[a].begin();
      i64 d = min(give[a], X - take[j]);
      take[j] += d;
      give[a] -= d;
      if (take[j] == X) {
        auto [b, c] = edges[j];
        merges[ds.leader(b)].erase(j);
        merges[ds.leader(c)].erase(j);
        q.push(j);
      }
    }
  };

  for (int i = 0; i < N; i++) {
    flow(i);
  }
  vector<int> ans;
  while (q.size() > 0) {
    int i = q.front();
    q.pop();
    ans.push_back(i);
    auto [a, b] = edges[i];
    a = merge(a, b);
    flow(a);
  }

#if !defined(ETHANKIM8683) or false
  cout << "YES\n";
  for (auto e : ans) {
    cout << e + 1 << '\n';
  }
#endif

#if defined(ETHANKIM8683) and true
  dsu _ds(N);
  vector<i64> _A(A.begin(), A.end());
  bool _ok = true;
  auto _merge = [&](int a, int b) -> void {
    a = _ds.leader(a);
    b = _ds.leader(b);
    _ok = _ok and _A[a] + _A[b] >= X;
    if (_ds.merge(a, b) == b) {
      swap(a, b);
    }
    _A[a] += _A[b];
  };
  for (auto i : ans) {
    auto [a, b] = edges[i];
    _merge(a, b);
  }
  cerr << (_ok ? "ok" : "wa");
#endif
}
