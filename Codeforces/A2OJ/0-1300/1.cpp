#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  I x_total = 0;
  I y_total = 0;
  I z_total = 0;
  while (n--) {
    I x, y, z;
    cin >> x >> y >> x;
    x_total += x;
    y_total += y;
    z_total += z;
  }
  if (!x_total && !y_total && !z_total)
    printf("YES");
  else
    printf("NO");
  return 0;
}