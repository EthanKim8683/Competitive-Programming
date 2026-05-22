#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

// https://cp-algorithms.com/graph/min_cost_flow.html

struct Edge {
  int from, to, cost, capacity;
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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector dist1(N, vector(N, vector<int>(2)));
  for (auto &g : dist1) {
    for (auto &r : g) {
      for (auto &e : r) {
        cin >> e;
      }
    }
  }

  vector dist2(N, vector(N, vector<int>(2)));
  for (auto &g : dist2) {
    for (auto &r : g) {
      for (auto &e : r) {
        cin >> e;
      }
    }
  }

  // is this min-cost max flow???

  tuple<int, int, vector<int>, vector<int>> ans = {INF, -1, {}, {}};
  for (int i = 0; i <= N; i++) {
    int cost1, cost2;
    vector<int> L(N), R(N);
    {
      vector<Edge> edges;
      auto add_edge = [&](int a, int b, int cost, int capacity) -> void {
        edges.push_back({a, b, cost, capacity});
      };

      for (int j = 0; j < N; j++) {
        add_edge(0, 1 + j, 0, 1);
      }
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          add_edge(1 + j, 1 + N + k, dist1[j][k][k >= i], 1);
        }
      }
      for (int j = 0; j < N; j++) {
        add_edge(1 + N + j, 1 + N + N, 0, 1);
      }

      cost1 = min_cost_flow(1 + N + N + 1, edges, N, 0, 1 + N + N);

      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          if (capacity[1 + j][1 + N + k] == 0) {
            L[j] = k;
          }
        }
      }
    }
    {
      vector<Edge> edges;
      auto add_edge = [&](int a, int b, int cost, int capacity) -> void {
        edges.push_back({a, b, cost, capacity});
      };

      for (int j = 0; j < N; j++) {
        add_edge(0, 1 + j, 0, 1);
      }
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          add_edge(1 + j, 1 + N + k, dist2[j][k][k >= i], 1);
        }
      }
      for (int j = 0; j < N; j++) {
        add_edge(1 + N + j, 1 + N + N, 0, 1);
      }

      cost2 = min_cost_flow(1 + N + N + 1, edges, N, 0, 1 + N + N);

      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          if (capacity[1 + j][1 + N + k] == 0) {
            R[j] = k;
          }
        }
      }
    }
    ans = min(ans, {cost1 + cost2, i, L, R});
  }

  auto [cost, i, L, R] = ans;
  vector<int> R_(N);
  for (int i = 0; i < N; i++) {
    R_[R[i]] = i;
  }

  cout << cost << '\n';
  for (int j = 0; j < N; j++) {
    cout << j + 1 << ' ' << L[j] + 1 << "AB"[L[j] >= i] << ' ' << R_[L[j]] + 1
         << '\n';
  }
}