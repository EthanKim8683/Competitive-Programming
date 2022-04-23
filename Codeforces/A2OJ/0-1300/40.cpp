#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("40.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U fives = 0;
  U zeros = 0;
  for (U i = n; i--;) {
    U a;
    cin >> a;
    if (a)
      fives++;
    else
      zeros++;
  }
  fives = fives / 9 * 9;
  if (zeros) {
    if (fives) {
      while (fives--)
        printf("5");
      while (zeros--)
        printf("0");
    } else
      printf("0");
  } else
    printf("-1");
  return 0;
}