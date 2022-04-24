#include <iostream>
#include <cstdio>
#include <algorithm>

#define N 100000

using namespace std;

using I = int;
using S = string;
using B = bool;
using C = char;

S strs[N];
I depth = 0;

B dfs(I a, I b) {
  const B parity = depth & 1;
  const I index = depth;
  B result = !parity;
  depth++;
  I r = a;
  while (r < b && strs[r][index] == '\0')
    r++;
  for (C i = 'a'; i <= 'z'; i++) {
    I l = r;
    while (r < b && strs[r][index] == i)
      r++;
    if (l < r && dfs(l, r) == parity) {
      result = parity;
      break;
    }
  }
  depth--;
  return result;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("455b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = n; i--;)
    cin >> strs[i];
  sort(strs, strs + n);
  I result = 0;
  if (dfs(0, n))
    result = !(k & 1);
  if (result)
    printf("Second\n");
  else
    printf("First\n");
  return 0;
}