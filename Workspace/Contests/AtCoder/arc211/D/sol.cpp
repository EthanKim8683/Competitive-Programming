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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // make tree rooted at 1, make tree rooted at 2
  //
  // parent array is not equal at any element
  //
  // if any node has only one adjacent element, there is no solution
  //
  // simplify down to graph where each node has degree at least 3
  //
  // adding edges to a graph made from adding degree 2 nodes always yields a
  // solution
  //
  // start with nodes 1 and 2, then add nodes which have edges to at least 2
  // nodes in the set
  //
  // pick a simple path between nodes 1 and 2 to start with
  // any simple path should work because if we don't pick nodes of some simple
  // path, they can get included later
  //
  // counterexample: we should sometimes add a couple nodes at a time

  int N, M;
  cin >> N >> M;

  vc<vi> adj(N);
  rep(i, 0, M) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  int included = 0;
  vc<vi> parents(N);
  queue<int> q;
  auto nudge = [&](int a) -> void {
    if (sz(parents[a]) < 2) return;
    q.push(a);
  };
  auto include = [&](int a) -> void {
    included += 1;
    for (auto b : adj[a]) {
      if (sz(parents[b]) == 2) continue;
      parents[b].pb(a);
      nudge(b);
    }
  };

  vc<bool> seen(N, false);
  vi stack;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;
    stack.pb(a);
    if (a == 1) {
      parents[0].pb(-1);
      parents[1].pb(-1);
      rep(i, 0, sz(stack) - 1) {
        parents[stack[i]].pb(stack[i + 1]);
        parents[stack[i + 1]].pb(stack[i]);
      }
      rep(i, 0, sz(stack)) { nudge(stack[i]); }
    }
    for (auto b : adj[a]) {
      self(self, b);
    }
    stack.pop_back();
  };
  dfs(dfs, 0);
  while (sz(q) > 0) {
    int a = q.front();
    q.pop();
    include(a);
  }

  if (included < N) {
    cout << "No\n";
    exit(0);
  }

  cout << "Yes\n";
  for (auto r : parents) {
    for (auto e : r) {
      if (e == -1) continue;
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
