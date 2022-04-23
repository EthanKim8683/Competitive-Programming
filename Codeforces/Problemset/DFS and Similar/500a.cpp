#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

I adjs[30000];
I t;

B dfs(I a) {
  if (a == t)
    return true;
  const I b = adjs[a];
  if (b != -1)
    return dfs(b);
  return false;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("500a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> t;
  fill_n(adjs, n, -1);
  t--;
  for (I i = 0; i < n - 1; i++) {
    I a;
    cin >> a;
    adjs[i] = i + a;
  }
  if (dfs(0))
    printf("YES");
  else
    printf("NO");
  return 0;
}