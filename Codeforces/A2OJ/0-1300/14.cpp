#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U as[100];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("14.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U a_min = -1;
  U a_max = 0;
  for (U i = n; i--;) {
    auto& a = as[i];
    cin >> a;
    a_min = min(a_min, a);
    a_max = max(a_max, a);
  }
  U result = 0;
  U a = 0;
  U b = n;
  while (as[a] != a_min && ++a < n)
    result++;
  while (--b && as[b] != a_max)
    result++;
  result -= a > b;
  printf("%u\n", result);
  return 0;
}