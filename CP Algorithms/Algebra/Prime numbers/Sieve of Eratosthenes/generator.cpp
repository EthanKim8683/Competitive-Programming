#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 1000000000;
const I SQTN = 31622;

vector<I> prms;
B coms[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  for (I i = 2; i <= SQTN; i++) {
    if (!coms[i]) {
      prms.push_back(i);
      for (I j = i * i; j <= SQTN; j += i)
        coms[j] = true;
    }
  }
  coms[0] = true;
  coms[1] = true;
  I t;
  cin >> t;
  while (t) {
    I m, n;
    cin >> m >> n;
    for (const auto prm : prms)
      for (I i = max((m + prm - 1) / prm, prm) * prm; i <= n; i += prm)
        coms[i] = true;
    for (I i = m; i <= n; i++)
      if (!coms[i])
        printf("%i\n", i);
    if (--t)
      printf("\n");
  }
  return 0;
}