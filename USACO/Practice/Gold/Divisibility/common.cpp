#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;
const I X = 1e6;

I x_arr[N];
B facs[X + 1];

int main(void) {
#ifdef ETHANKIM8683
  freopen("common.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  I res = 1;
  for (I i = 0; i < n; i++) {
    const auto x = x_arr[i];
    if (facs[x])
      res = max(res, x);
    else {
      for (I j = 1; j * j <= x; j++) {
        if (x % j == 0) {
          const I k = x / j;
          if (facs[j])
            res = max(res, j);
          if (facs[k])
            res = max(res, k);
          facs[j] = true;
          facs[k] = true;
        }
      }
    }
  }
  printf("%i\n", res);
  return 0;
}