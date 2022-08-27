#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using C = char;

Lli cnts[10];
C cdf[] = "codeforces";

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  Lli n;
  cin >> n;
  Lli val = 1;
  fill_n(cnts, 10, 1);
  while (true) {
    for (I i = 0; i < 10; i++) {
      if (val >= n) {
        for (I j = 0; j < 10; j++)
          for (I k = 0; k < cnts[j]; k++)
            printf("%c", cdf[j]);
        return 0;
      }
      val /= cnts[i]++;
      val *= cnts[i];
    }
  }
  return 0;
}