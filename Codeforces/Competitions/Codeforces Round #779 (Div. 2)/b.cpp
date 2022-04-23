#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

#define MOD(x) ((x) % 998244353llu)

using namespace std;

using U = unsigned int;
using Ull = unsigned long long;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("b.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    if (n & 1)
      printf("0\n");
    else {
      Ull r = 1;
      Ull f = 1;
      while (n -= 2)
        r = MOD(r * ++f);
      printf("%llu\n", MOD(r * r));
    }
  }
}