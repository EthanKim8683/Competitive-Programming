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
  while (t--) {
    I a, b;
    cin >> a >> b;
    const I g = gcd(a, b);
    const I l = a / g * b;
    printf("%i %i\n", g, l);
  }
  return 0;
}