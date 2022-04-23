#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

I main(void) {
#ifdef ETHANKIM8683
  freopen("1352f.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n0, n1, n2;
    cin >> n0 >> n1 >> n2;
    if (n1)
      if (n1 % 2 == 0)
        printf("0");
    if (n2)
      for (I i = n2 + !n1; i--;)
        printf("1");
    for (I i = (n1 + 1) / 2; i--;)
      printf("10");
    if (n0)
      for (I i = n0 + !n1; i--;)
        printf("0");
    printf("\n");
  }
  return 0;
}