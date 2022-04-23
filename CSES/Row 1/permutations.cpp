// start 8:51
// end 9:00
// tries 

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("permutations.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  if (n == 1)
    printf("1");
  else if (n == 4)
    printf("2 4 1 3");
  else if (n < 5)
    printf("NO SOLUTION\n");
  else {
    const U h = n >> 1;
    const U o = h + (n & 1);
    for (U i = 1; i <= h; i++) {
      printf("%u ", i);
      printf("%u ", i + o);
    }
    if (n & 1)
      printf("%u", h + 1);
  }
  return 0;
}