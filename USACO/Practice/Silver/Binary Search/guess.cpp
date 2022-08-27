#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

I k;

B tes(I pos) {
  printf("? %i %i\n", 1, pos + 1);
  fflush(stdout);
  I cnt;
  cin >> cnt;
  return (pos + 1) - cnt >= k;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, t;
  cin >> n >> t;
  while (t--) {
    cin >> k;
    I l = 0;
    I r = n - 1;
    while (l < r) {
      const I m = l + (r - l) / 2;
      if (tes(m))
        r = m;
      else
        l = m + 1;
    }
    printf("! %i\n", l + 1);
    fflush(stdout);
  }
  return 0;
}