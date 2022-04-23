#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("2.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  for (I i = 5; i--;) {
    for (I j = 5; j--;) {
      U x;
      cin >> x;
      if (x) {
        printf("%i\n", abs(i - 2) + abs(j - 2));
        return 0;
      }
    }
  }
  return 0;
}