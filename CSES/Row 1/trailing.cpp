// start 9:41
// end 9:55
// tries 

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("trailing.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U x = 0;
  for (U i = 5; n / i >= 1; i *= 5)
    x += n / i;
  printf("%u\n", x);
  return 0;
}