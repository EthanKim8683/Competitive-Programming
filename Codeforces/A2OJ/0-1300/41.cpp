#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("41.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  Llu result = 0;
  U l = 0;
  while (m--) {
    U a;
    cin >> a;
    a--;
    if (a < l)
      result += n - l + a;
    else
      result += a - l;
    l = a;
  }
  printf("%llu\n", result);
  return 0;
}