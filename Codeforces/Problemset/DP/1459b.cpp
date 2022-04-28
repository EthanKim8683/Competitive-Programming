#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

I main(void) {
#ifdef ETHANKIM8683
  freopen("1459b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  Lli n;
  cin >> n;
  printf("%lli\n", (n / 2 + 1) * ((n + 1) / 2 + 1) * (n % 2 + 1));
  return 0;
}