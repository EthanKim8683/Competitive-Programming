#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

vector<I> adjs[100000];
B cats[100000];
I m;

I dfs(I a, I p = -1, I c = 0) {
  if (cats[a])
    c++;
  else
    c = 0;
  if (c > m)
    return 0;
  const auto adj = adjs[a];
  I result = 0;
  B leaf = true;
  for (const auto b : adj) {
    if (b != p) {
      result += dfs(b, a, c);
      leaf = false;
    }
  }
  return result + leaf;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("580c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> cats[i];
  for (I i = n; --i;) {
    I x, y;
    cin >> x >> y;
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  printf("%i", dfs(0));
  return 0;
}