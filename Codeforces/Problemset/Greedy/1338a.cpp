#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 1e5;

I a_arr[N];

I log(I x) {
  if (x <= 0)
    return 0;
  return 31 - __builtin_clz(x);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    for (I i = 0; i < n; i++)
      cin >> a_arr[i];
    I res = 0;
    I end = a_arr[0];
    for (I i = 1; i < n; i++) {
      const I a = a_arr[i];
      if (end > a)
        res = max(res, log(end - a) + 1);
      else
        end = a;
    }
    printf("%i\n", res);
  }
  return 0;
}