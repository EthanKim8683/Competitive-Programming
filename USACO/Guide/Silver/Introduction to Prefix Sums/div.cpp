#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using Lli = long long int;

Llu r_count[200000] = { 1 };

int main(void) {
#if defined(ETHANKIM8683)
  freopen("div.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  Lli r = 0;
  Llu result = 0;
  for (U i = n; i--;) {
    Lli a;
    cin >> a;
    r = (r + a) % n;
    if (r < 0)
      r += n;
    result += r_count[r];
    r_count[r]++;
  }
  printf("%llu\n", result);
  return 0;
}