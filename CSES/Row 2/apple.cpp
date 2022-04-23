// start 8:53
// end 9:02
// tries 3

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using Lli = long long int;

U a[20];
U n;

Llu dfs(U i, Llu x, Llu y) {
  if (i >= n)
    return abs((Lli) (x - y));
  const Llu v = a[i];
  i++;
  return min(dfs(i, x + v, y), dfs(i, x, y + v));
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("apple.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (U i = n; i--;)
    cin >> a[i];
  printf("%llu\n", dfs(0, 0, 0));
  return 0;
}