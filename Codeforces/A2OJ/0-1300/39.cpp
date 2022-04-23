#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("39.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  switch (n) {
    case 0:
      printf("0 0 0\n");
      break;
    case 1:
      printf("0 0 1\n");
      break;
    case 2:
      printf("0 1 1\n");
      break;
    default:;
      U a = 0;
      U b = 1;
      U c = 1;
      U d = 2;
      while (a + b + d < n) {
        a = b;
        b = c;
        c = d;
        d = b + c;
      }
      printf("%u %u %u\n", a, b, d);
      break;
  }
  return 0;
}