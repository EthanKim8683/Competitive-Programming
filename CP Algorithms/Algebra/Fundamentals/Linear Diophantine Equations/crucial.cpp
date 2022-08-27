#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

I gcd(I a, I b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  for (I i = 1; i <= t; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    if (c % gcd(a, b) == 0)
      printf("Case %i: Yes\n", i);
    else
      printf("Case %i: No\n", i);
  }
  return 0;
}