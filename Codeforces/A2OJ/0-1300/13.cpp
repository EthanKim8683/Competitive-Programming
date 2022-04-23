#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("13.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  if (n & 1)
    printf("-1");
  else {
    U a = 2;
    for (U i = n; i--;) {
      printf("%u ", a);
      if (i & 1)
        a--;
      else
        a += 3;
    }
  }
  return 0;
}