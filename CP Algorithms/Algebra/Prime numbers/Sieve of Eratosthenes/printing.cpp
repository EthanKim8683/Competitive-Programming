#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I N = 1e8;

B coms[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  coms[0] = true;
  coms[1] = true;
  for (I i = 2; i * i < N; i++)
    if (!coms[i])
      for (I j = i * i; j < N; j += i)
        coms[j] = true;
  I cnt = 0;
  for (I i = 0; i < N; i++) {
    if (!coms[i]) {
      if (cnt == 0)
        printf("%i\n", i);
      cnt = (cnt + 1) % 100;
    }
  }
  return 0;
}