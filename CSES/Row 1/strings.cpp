// start 9:37
// end 9:41
// tries 

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("strings.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  Llu e = 1;
  while (n--)
    e = e * 2 % 1000000007;
  printf("%llu\n", e);
  return 0;
}