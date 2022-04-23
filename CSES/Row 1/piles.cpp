// start 9:55
// end 10:00
// tries 

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("piles.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    I a, b;
    cin >> a >> b;
    I m = min(a, b);
    I d = max(a, b) - m;
    m -= d;
    if (m >= 0 && !(m % 3))
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}