#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("16.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U k, l, m, n, d;
  cin >> k >> l >> m >> n >> d;
  U result = 0;
  for (U i = d + 1; --i;)
    result += !(i % k) || !(i % l) || !(i % m) || !(i % n);
  printf("%u\n", result);
  return 0;
}