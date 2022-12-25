#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[100000];
pair<U, U> cows[100000];
B visited[100000];
U min_x;
U min_y;
U max_x;
U max_y;

void dfs(U a) {
  visited[a] = true;
  const auto [x, y] = cows[a];
  min_x = min(min_x, x);
  min_y = min(min_y, y);
  max_x = max(max_x, x);
  max_y = max(max_y, y);
  for (const auto b : adjs[a])
    if (!visited[b])
      dfs(b);
}

int main(void) {
  freopen("fenceplan.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("fenceplan.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U i = 0; i < n; i++) {
    auto& cow = cows[i];
    cin >> cow.first >> cow.second;
  }
  while (m--) {
    U a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  U result = -1;
  for (U i = n; i--;) {
    if (!visited[i]) {
      min_x = -1;
      min_y = -1;
      max_x = 0;
      max_y = 0;
      dfs(i);
      result = min(result, max_x - min_x + max_y - min_y);
    }
  }
  printf("%u\n", result * 2);
  return 0;
}