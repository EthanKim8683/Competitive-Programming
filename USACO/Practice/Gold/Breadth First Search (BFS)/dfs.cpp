#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

using I = int;
using B = bool;

const I N = 4096;

I bfs_ords[N];
I dfs_ords[N];
B usds[N + 1][N + 1];
vector<pair<I, I>> ress;
vector<I> adjs[N + 1];
queue<I> que;
B bfs_viss[N + 1];
B dfs_viss[N + 1];
I bfs_ind = 0;
I dfs_ind = 0;

B bfs() {
  que.push(1);
  while (!que.empty()) {
    const auto a = que.front();
    que.pop();
    if (!bfs_viss[a]) {
      bfs_viss[a] = true;
      if (bfs_ords[bfs_ind++] != a)
        return true;
      for (const auto b : adjs[a])
        if (!bfs_viss[b])
          que.push(b);
    }
  }
  return false;
}

B dfs(I a = 1) {
  dfs_viss[a] = true;
  if (dfs_ords[dfs_ind++] != a)
    return true;
  for (const auto b : adjs[a])
    if (!dfs_viss[b])
      if (dfs(b))
        return true;
  return false;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("dfs.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> bfs_ords[i];
  for (I i = 0; i < n; i++)
    cin >> dfs_ords[i];
  for (I i = 1; i < n; i++) {
    const auto a = dfs_ords[i - 1];
    const auto b = dfs_ords[i];
    if (!usds[a][b]) {
      usds[a][b] = true;
      usds[b][a] = true;
      ress.push_back({a, b});
      adjs[a].push_back(b);
      adjs[b].push_back(a);
    }
  }
  for (I i = 1; i < n; i++) {
    const auto b = bfs_ords[i];
    if (!usds[1][b]) {
      ress.push_back({1, b});
      adjs[1].push_back(b);
      adjs[b].push_back(1);
    }
  }
  if (bfs() || dfs())
    printf("-1\n");
  else {
    printf("%i\n", ress.size());
    for (const auto [a, b] : ress)
      printf("%i %i\n", a, b);
  }
  return 0;
}