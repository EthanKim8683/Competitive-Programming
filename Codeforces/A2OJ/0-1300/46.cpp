#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;

I as[100];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("46.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U i = n; i--;)
    cin >> as[i];
  sort(as, as + n);
  U result = 0;
  for (U i = 0; i < m; i++) {
    const auto a = as[i];
    if (a >= 0)
      break;
    result -= a;
  }
  printf("%u\n", result);
  return 0;
}