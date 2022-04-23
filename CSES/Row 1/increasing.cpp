// start 8:45
// end 8:50
// tries 2

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)S
  freopen("increasing.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U l;
  cin >> l;
  Llu m = 0;
  while (--n) {
    U a;
    cin >> a;
    if (a < l)
      m += l - a;
    else
      l = a;
  }
  printf("%llu\n", m);
  return 0;
}