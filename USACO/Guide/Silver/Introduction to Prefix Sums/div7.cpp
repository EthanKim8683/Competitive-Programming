#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

I r_beg[7] = { 1 };
I r_end[7];

int main(void) {
  freopen("div7.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("div7.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U r = 0;
  for (U i = 1; i <= n;) {
    U id;
    cin >> id;
    r = (r + id) % 7;
    i++;
    if (r_beg[r])
      r_end[r] = i;
    else
      r_beg[r] = i;
  }
  I m = 0;
  for (U r = 7; r--;)
    m = max(m, r_end[r] - r_beg[r]);
  printf("%i\n", m);
  return 0;
}