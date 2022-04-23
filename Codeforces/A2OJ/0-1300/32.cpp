#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U as[100];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("32.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  U a_max = 0;
  for (U i = n; i--;) {
    U a;
    cin >> a;
    as[i] = a;
    a_max = max(a_max, a);
  }
  U a_low = (a_max - 1) / m * m;
  U result = 0;
  for (U i = n; i--;)
    if (as[i] > a_low)
      result = i;
  printf("%u\n", n - result);
  return 0;
}