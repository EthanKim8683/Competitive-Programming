#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;

U as[12];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("48.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U k;
  cin >> k;
  if (k) {
    for (U i = 12; i--;)
      cin >> as[i];
    sort(as, as + 12, greater<U>());
    U i = 0;
    for (; i < 12; i++) {
      const auto a = as[i];
      if (a >= k)
        break;
      k -= a;
    }
    if (i == 12)
      printf("-1");
    else
      printf("%u", i + 1);
  } else
    printf("0");
  return 0;
}