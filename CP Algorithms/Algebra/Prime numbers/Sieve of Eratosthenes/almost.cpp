#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 3000;

I facs[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 2; i <= n; i++)
    if (facs[i] == 0)
      for (I j = i + i; j <= n; j += i)
        facs[j]++;
  I res = 0;
  for (I i = 1; i <= n; i++)
    res += facs[i] == 2;
  printf("%i\n", res);
  return 0;
}