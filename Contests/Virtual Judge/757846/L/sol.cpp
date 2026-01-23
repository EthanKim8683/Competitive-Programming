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

const int INF = 1e18;

// https://cp-algorithms.com/graph/min_cost_flow.html

struct Edge {
  int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;

void shortest_paths(int n, int v0, vector<int> &d, vector<int> &p) {
  d.assign(n, INF);
  d[v0] = 0;
  vector<bool> inq(n, false);
  queue<int> q;
  q.push(v0);
  p.assign(n, -1);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    for (int v : adj[u]) {
      if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
        d[v] = d[u] + cost[u][v];
        p[v] = u;
        if (!inq[v]) {
          inq[v] = true;
          q.push(v);
        }
      }
    }
  }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
  adj.assign(N, vector<int>());
  cost.assign(N, vector<int>(N, 0));
  capacity.assign(N, vector<int>(N, 0));
  for (Edge e : edges) {
    adj[e.from].push_back(e.to);
    adj[e.to].push_back(e.from);
    cost[e.from][e.to] = e.cost;
    cost[e.to][e.from] = -e.cost;
    capacity[e.from][e.to] = e.capacity;
  }

  int flow = 0;
  int cost = 0;
  vector<int> d, p;
  while (flow < K) {
    shortest_paths(N, s, d, p);
    if (d[t] == INF) break;

    // find max flow on that path
    int f = K - flow;
    int cur = t;
    while (cur != s) {
      f = min(f, capacity[p[cur]][cur]);
      cur = p[cur];
    }

    // apply flow
    flow += f;
    cost += f * d[t];
    cur = t;
    while (cur != s) {
      capacity[p[cur]][cur] -= f;
      capacity[cur][p[cur]] += f;
      cur = p[cur];
    }
  }

  if (flow < K)
    return -1;
  else
    return cost;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc A(N, vi(M));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vc D(N, vi(N));
  for (auto &r : D) {
    for (auto &e : r) {
      cin >> e;
      if (e == -1) {
        e = INF;
      }
    }
  }

  rep(i, 0, N) {
    rep(j, 0, N) {
      rep(k, 0, N) { D[j][k] = min(D[j][k], D[j][i] + D[i][k]); }
    }
  }

  vc<Edge> edges;
  rep(i, 0, N) { edges.eb(0, 1 + i, 1, 0); }
  rep(i, 0, M) { edges.eb(1 + N + i, 1 + N + M, 1, 0); }
  rep(i, 0, M) {
    rep(j, 0, N) {
      int sum = 0;
      rep(k, 0, N) { sum += A[k][i] * D[k][j]; }
      edges.eb(1 + j, 1 + N + i, 1, sum);
    }
  }
  cout << min_cost_flow(1 + N + M + 1, edges, M, 0, 1 + N + M);
}