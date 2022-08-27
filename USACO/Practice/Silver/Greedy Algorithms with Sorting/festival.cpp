#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

pair<I, I> movs[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, b;
    cin >> a >> b;
    movs[i] = {b, a};
  }
  sort(movs, movs + n);
  I end = 0;
  I res = 0;
  for (I i = 0; i < n; i++) {
    const auto [b, a] = movs[i];
    if (a >= end) {
      end = b;
      res++;
    }
  }
  printf("%i\n", res);
  return 0;
}