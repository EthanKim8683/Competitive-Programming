#include <iostream>
#include <cstdio>
#include <algorithm>

#define N 100000

using namespace std;

using I = int;

I a_arr[N];
I depth = 29;

I dfs(I a, I b, I bitmask) {
  if (depth >= 0) {
    const I bit = 1 << depth;
    I l = a;
    I r = b;
    while (l < r) {
      const I m = l + (r - l) / 2;
      if (a_arr[m] & bit)
        r = m;
      else
        l = m + 1;
    }
    depth--;
    I result;
    if (l == a)
      result = dfs(a, b, bitmask | bit);
    else if (l == b)
      result = dfs(a, b, bitmask);
    else
      result = min(dfs(a, l, bitmask | bit), dfs(l, b, bitmask));
    depth++;
    return result;
  } else
    return a_arr[a] ^ bitmask;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1285d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = n; i--;)
    cin >> a_arr[i];
  sort(a_arr, a_arr + n);
  printf("%i\n", dfs(0, n, 0));
  return 0;
}