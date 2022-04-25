#include <iostream>
#include <cstdio>
#include <vector>

#define N 100000

using namespace std;

using I = int;
using C = char;
using B = bool;

vector<I> adjs[N];
B viss[N];
I pars[N];
I ress[N];
I far_d;
I far_a;
I dep = 0;
C res = 'A';
B imp = false;

void dfs1(I a, I p = -1) {
  if (viss[a])
    return;
  if (dep > far_d) {
    far_d = dep;
    far_a = a;
  }
  pars[a] = p;
  dep++;
  for (const auto b : adjs[a])
    if (b != p)
      dfs1(b, a);
  dep--;
}

void dfs2(I a) {
  if (imp || viss[a])
    return;
  if (res > 'Z') {
    imp = true;
    return;
  }
  far_d = 0;
  dfs1(a);
  if (far_d) {
    far_d = 0;
    dfs1(far_a);
    if (far_d) {
      I r = far_a;
      for (I i = far_d / 2; i--;)
        r = pars[r];
      viss[r] = true;
      ress[r] = res;
      res++;
      for (const auto b : adjs[r])
        dfs2(b);
      res--;
      return;
    }
  }
  viss[a] = true;
  ress[a] = res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("321c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = n; --i;) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs2(0);
  if (imp)
    printf("Impossible!");
  else
    for (I i = 0; i < n; i++)
      printf("%c ", ress[i]);
  return 0;
}