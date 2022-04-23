#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("b.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  while (n--) {
    U a;
    cin >> a;
    if (a) {
      U result = 32768;
      for (U x = 0; x < result; x++) {
        const U y = 15 - __builtin_ctz(a);
        result = min(result, x + y);
        a++;
      }
      printf("%u ", result);
    } else
      printf("16 ");
  }
  return 0;
}