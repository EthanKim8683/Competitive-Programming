#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

U hs[300000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("c.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    U h_max = 0;
    for (U i = n; i--;) {
      U h;
      cin >> h;
      hs[i] = h;
      h_max = max(h_max, h);
    }
    Llu odds = 0llu;
    Llu evens = 0llu;
    for (U i = n; i--;) {
      const U h = hs[i];
      const U disp = h_max - h;
      const U even = disp / 2;
      evens += even;
      odds += disp - even * 2;
    }
    if (evens > odds) {
      const U disp = (evens - odds) / 3llu;
      evens -= disp;
      odds = evens;
    } else if (evens < odds)
      evens = odds - 1llu;
    printf("%llu\n", evens + odds);
  }
  return 0;
}