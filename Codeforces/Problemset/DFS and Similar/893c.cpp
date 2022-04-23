#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using B = bool;

vector<U> adjs[100000];
pair<Llu, U> costs[100000];
B visited[100000];

void dfs(U a) {
  if (visited[a])
    return;
  visited[a] = true;
  for (const auto b : adjs[a])
    dfs(b);
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("893c.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U i = 0; i < n; i++) {
    auto& cost = costs[i];
    cin >> cost.first;
    cost.second = i;
  }
  sort(costs, costs + n);
  for (U i = m; i--;) {
    U x, y;
    cin >> x >> y;
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  Llu result = 0;
  for (U i = 0; i < n; i++) {
    const auto [cost, a] = costs[i];
    if (!visited[a]) {
      result += cost;
      dfs(a);
    }
  }
  printf("%llu\n", result);
  return 0;
}