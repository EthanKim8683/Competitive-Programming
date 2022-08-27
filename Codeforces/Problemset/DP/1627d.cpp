#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I N = 1e6;
const I A = 1e6;

I a_arr[N];
I gcds[A + 1];
B vals[A + 1];
B coms[A + 1];

I gcd(I a, I b) {
  if (a == 0)
    return b;
  if (b == 0)
    return a;
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++) {
    const I a = a_arr[i];
    vals[a] = true;
    gcds[1] = gcd(gcds[1], a);
    gcds[a] = gcd(gcds[a], 1);
  }
  for (I i = 2; i * i <= A; i++) {
    for (I j = 2; i * j <= A; j++) {
      coms[i * j] = true;
      if (vals[i * j]) {
        gcds[i] = gcd(gcds[i], j);
        gcds[j] = gcd(gcds[j], i);
      }
    }
  }
  I res = 0;
  for (I i = 1; i <= A; i++)
    res += gcds[i] == 1;
  printf("%i\n", res - n);
  return 0;
}