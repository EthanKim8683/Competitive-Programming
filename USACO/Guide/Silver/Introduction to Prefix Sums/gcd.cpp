#include <iostream>
#include <cstdio>
#include<numeric>

using namespace std;

using U = unsigned;

U a[100000];
U lo_ps[100000];
U hi_ps[100000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("gcd.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  const U m = n - 1;
  for (U i = 0; i < n; i++) {
    U i_a;
    cin >> i_a;
    a[i] = i_a;
  }
  U lo_gcd = a[0];
  U hi_gcd = a[m];
  for (U x = 1; x < n; x++) {
    const U y = m - x;
    lo_ps[x] = lo_gcd;
    hi_ps[y] = hi_gcd;
    lo_gcd = gcd(lo_gcd, a[x]);
    hi_gcd = gcd(hi_gcd, a[y]);
  }
  U result = 1;
  for (U i = 0; i < n; i++)
    result = max(result, gcd(lo_ps[i], hi_ps[i]));
  printf("%u\n", result);
  return 0;
}