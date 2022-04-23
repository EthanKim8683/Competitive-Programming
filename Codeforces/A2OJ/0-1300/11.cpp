#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using B = bool;

B sieve[51];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("11.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U i = 2; i < m; i++)
    for (U o = i * 2; o <= m; o += i)
      sieve[o] = true;
  if (!sieve[m])
    while (++n <= m && sieve[n]);
  if (n == m)
    printf("YES");
  else
    printf("NO");
  return 0;
}