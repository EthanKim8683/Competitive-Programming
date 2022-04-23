#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned int;
using I = int;
using B = bool;

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
    I f;
    cin >> f;
    I l = f;
    B r = true;
    U i = f == 1;
    while (--n) {
      I c;
      cin >> c;
      r &= c - l <= 1;
      i += c == 1;
      l = c;
    }
    if (r && f - l <= 1 && i == 1)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}