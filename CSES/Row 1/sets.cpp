// start 9:24
// end 9:31
// tries 2

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("sets.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  switch (n % 4) {
    case 0: {
      printf("YES");
      const U h = n >> 1;
      printf("\n%u\n", h);
      U v = 1;
      for (U i = 0; i < h; i++) {
        printf("%u ", v);
        v += i & 1 ? 1 : 3;
      }
      printf("\n%u\n", h);
      v = 2;
      for (U i = 0; i < h; i++) {
        printf("%u ", v);
        v += i & 1 ? 3 : 1;
      }
      break;
    }
    case 3: {
      printf("YES");
      const U h = n >> 1;
      printf("\n%u\n", h + 1);
      U v = 1;
      for (U i = 0; i <= h; i++) {
        printf("%u ", v);
        v += i & 1 ? 3 : 1;
      }
      printf("\n%u\n", h);
      v = 3;
      for (U i = 0; i < h; i++) {
        printf("%u ", v);
        v += i & 1 ? 3 : 1;
      }
      break;
    }
    default:
      printf("NO");
      break;
  }
  return 0;
}