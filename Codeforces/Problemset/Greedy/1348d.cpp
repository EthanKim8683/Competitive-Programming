#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I LOGN = 30;

I ress[LOGN];

I log(I val) {
  return 31 - __builtin_clz(val);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    if (n == 2) {
      printf("1\n0\n");
      continue;
    }
    if (n == 3) {
      printf("1\n1\n");
      continue;
    }
    const I cnt = log(n);
    I pow = 1;
    I sum = 1;
    for (I i = 0; i < cnt - 2; i++) {
      ress[i] = pow;
      pow *= 2;
      sum += pow;
    }
    const I dif = n - sum;
    const I low = min(dif / 2, pow * 2);
    const I upp = dif - low;
    ress[cnt - 2] = low - pow;
    ress[cnt - 1] = upp - low;
    printf("%i\n", cnt);
    for (I i = 0; i < cnt; i++)
      printf("%i ", ress[i]);
    printf("\n");
  }
  return 0;
}