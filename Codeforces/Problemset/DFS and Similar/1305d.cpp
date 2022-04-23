#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[1000];
B visited[1000];
U depth = 0;
U farthest_depth;
U farthest_index;
U u, v;

void dfs1(U a, U p = -1) {
  if (depth > farthest_depth) {
    farthest_depth = depth;
    farthest_index = a;
  }
  depth++;
  for (const auto b : adjs[a])
    if (b != p && !visited[b])
      dfs1(b, a);
  depth--;
}

B dfs2(U a, U p = -1) {
  if (a == u || a == v)
    return true;
  for (const auto b : adjs[a])
    if (b != p && dfs2(b, a))
      return true;
  return false;
}

int main(void) {
  cin.tie(0)->sync_with_stdio(0);
  U n;
  scanf("%u", &n);
  for (U i = n; --i;) {
    U x, y;
    scanf("%u %u", &x, &y);
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  u = 0;
  for (U i = n / 2; i--;) {
    farthest_depth = 0;
    farthest_index = -1;
    dfs1(u);
    if (farthest_index == -1)
      break;
    v = farthest_index;
    farthest_depth = 0;
    dfs1(v);
    u = farthest_index;
    printf("? %u %u\n", u + 1, v + 1);
    fflush(stdout);
    U w;
    scanf("%u", &w);
    w--;
    for (const auto b : adjs[w])
      if (dfs2(b, w))
        visited[b] = true;
    u = w;
  }
  printf("! %u\n", u + 1);
  fflush(stdout);
  return 0;
}