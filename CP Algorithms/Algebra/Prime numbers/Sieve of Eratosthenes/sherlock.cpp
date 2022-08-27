#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I N = 100000;

B coms[N + 1 + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  B res = 0;
  for (I i = 2; i <= n + 1; i++)
    if (coms[i] == 0)
      for (I j = i + i; j <= n + 1; j += i)
        res |= (coms[j] = true);
  printf("%i\n", res + 1);
  for (I i = 2; i <= n + 1; i++)
    printf("%i ", coms[i] + 1);
  return 0;
}