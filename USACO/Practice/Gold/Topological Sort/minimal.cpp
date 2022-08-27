#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using I = int;

const I N = 1e5;

vector<I> adjs[N];
I outs[N];
priority_queue<I> que;
vector<I> tops;
I invs[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I v, u;
    cin >> v >> u;
    v--;
    u--;
    adjs[u].push_back(v);
    outs[v]++;
  }
  for (I i = 0; i < n; i++)
    if (outs[i] == 0)
      que.push(i);
  while (!que.empty()) {
    const auto u = que.top();
    que.pop();
    tops.push_back(u);
    for (const auto v : adjs[u])
      if (--outs[v] == 0)
        que.push(v);
  }
  reverse(tops.begin(), tops.end());
  for (I i = 0; i < n; i++)
    invs[tops[i]] = i;
  for (I i = 0; i < n; i++)
    printf("%i ", invs[i] + 1);
  return 0;
}