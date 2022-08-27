#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 500;
const I MAX = 1e9;

vector<I> adjs[N];
I ress[N];
I viss[N];
I n;

B dfs(I a, I p) {
  if (a == p)
    return true;
  if (viss[a])
    return false;
  viss[a] = true;
  for (const auto b : adjs[a])
    if (dfs(b, p))
      return true;
  return false;
}

void slv(I a) {
  fill_n(viss, n, false);
  for (const auto b : adjs[a]) {
    if (dfs(b, a)) {
      ress[a] = b;
      return;
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    B rea = true;
    for (I j = 0; j < n; j++) {
      I pre;
      cin >> pre;
      pre--;
      if (pre == i)
        rea = false;
      if (rea)
        adjs[i].push_back(pre);
    }
  }
  iota(ress, ress + n, 0);
  for (I i = 0; i < n; i++)
    slv(i);
  for (I i = 0; i < n; i++)
    printf("%i\n", ress[i] + 1);
  return 0;
}