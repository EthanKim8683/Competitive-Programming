#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<I> adjs[N];
vector<I> ress;
B viss[N];
I inds[N];

void dfs(I a) {
  if (!viss[a]) {
    viss[a] = true;
    for (const auto b : adjs[a])
      dfs(b);
    ress.push_back(a);
  }
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("course.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  for (I i = 0; i < n; i++)
    dfs(i);
  reverse(ress.begin(), ress.end());
  for (I i = 0; i < ress.size(); i++)
    inds[ress[i]] = i;
  for (I i = 0; i < n; i++) {
    for (const auto b : adjs[i]) {
      if (inds[i] > inds[b]) {
        printf("IMPOSSIBLE\n");
        return 0;
      }
    }
  }
  for (const auto res : ress)
    printf("%i ", res + 1);
  printf("\n");
  return 0;
}