#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;
const I MAX = 1e9;

vector<I> outs[N];
vector<I> ins[N];
vector<I> tops;
queue<pair<I, I>> que;
priority_queue<pair<I, I>> pue[2];
B viss[N];
I deps[N];
I ress[N][2];
I n;

// topological sort does not work 100% with cycles

void bfs() {
  fill_n(viss, n, false);
  que.push({0, 0});
  while (!que.empty()) {
    const auto [a, dep] = que.front();
    que.pop();
    if (!viss[a]) {
      viss[a] = true;
      deps[a] = dep;
      for (const auto b : outs[a])
        que.push({b, dep + 1});
    }
  }
}

void djk() {
  for (I i = 0; i < n; i++)
    pue[0].push({ress[i][0], i});
  while (!pue[0].empty()) {
    const auto [dis, a] = pue[0].top();
    pue[0].pop();
    if (dis == ress[a][0]) {
      for (const auto b : ins[a]) {
        if (deps[b] < deps[a]) {
          if (dis < ress[b][0])
            pue[0].push({ress[b][0] = dis, b});
        } else {
          if (dis < ress[b][1])
            pue[1].push({ress[b][1] = dis, b});
        }
      }
    }
  }
  while (!pue[1].empty()) {
    const auto [dis, a] = pue[1].top();
    pue[1].pop();
    if (dis == ress[a][1])
      for (const auto b : ins[a])
        if (deps[b] < deps[a])
          if (dis < ress[b][1])
            pue[1].push({ress[b][1] = dis, b});
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I m;
    cin >> n >> m;
    for (I i = 0; i < n; i++) {
      outs[i].clear();
      ins[i].clear();
    }
    for (I i = 0; i < m; i++) {
      I a, b;
      cin >> a >> b;
      a--;
      b--;
      outs[a].push_back(b);
      ins[b].push_back(a);
    }
    bfs();
    for (I i = 0; i < n; i++) {
      ress[i][0] = deps[i];
      ress[i][1] = MAX;
    }
    djk();
    for (I i = 0; i < n; i++)
      printf("%i ", min(ress[i][0], ress[i][1]));
    printf("\n");
  }
  return 0;
}