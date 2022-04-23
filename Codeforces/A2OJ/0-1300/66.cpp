#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("66.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  k--;
  U result = k;
  U p = 0;
  U c = 1;
  while (k--) {
    U a;
    cin >> a;
    if (p == a)
      c++;
    else
      c = 1;
    p = a;
    n--;
  }
  U l;
  cin >> l;
  while (--n) {
    U a;
    cin >> a;
    if (l != a) {
      printf("-1");
      return 0;
    }
    l = a;
  }
  if (p == l)
    result -= c;
  printf("%u\n", result);
  return 0;
}