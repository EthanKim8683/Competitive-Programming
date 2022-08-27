#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

B viss[N];
B cols[N];
vector<I> adjs[N];

B dfs(I a, B col) {
  if (viss[a])
    return cols[a] == col;
  viss[a] = true;
  cols[a] = col;
  for (const auto b : adjs[a])
    if (!dfs(b, !col))
      return false;
  return true;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for (I i = 0; i < n; i++) {
    if (!viss[i]) {
      if (!dfs(i, false)) {
        printf("IMPOSSIBLE\n");
        return 0;
      }
    }
  }
  for (I i = 0; i < n; i++)
    printf("%i ", cols[i] + 1);
  return 0;
}