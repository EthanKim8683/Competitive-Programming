#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("17.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U l_total = 0;
  U r_total = 0;
  for (U i = n; i--;) {
    U l, r;
    cin >> l >> r;
    l_total += l;
    r_total += r;
  }
  const U l_change = min(l_total, n - l_total);
  const U r_change = min(r_total, n - r_total);
  printf("%u\n", l_change + r_change);
  return 0;
}