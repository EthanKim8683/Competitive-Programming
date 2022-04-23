#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("47.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  U result = 0;
  for (U a = 0; a * a <= n; a++)
    for (U b = 0; b * b <= m; b++)
      result += a * a + b == n && a + b * b == m;
  printf("%u\n", result);
  return 0;
}