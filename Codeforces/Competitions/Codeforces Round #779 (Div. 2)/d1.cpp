#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned int;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("d1.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U l, r;
    cin >> l >> r;
    U res[17] = { 0 };
    U ref[17] = { 0 };
    for (U i = l; i <= r; i++) {
      U a;
      cin >> a;
      for (U d = 17; d--;) {
        res[d] += a >> d & 1;
        ref[d] += i >> d & 1;
      }
    }
    U t = 0;
    for (U d = 17; d--;)
      if (res[d] != ref[d])
        t |= 1 << d;
    printf("%u\n", t);
  }
  return 0;
}