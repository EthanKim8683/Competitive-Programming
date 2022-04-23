#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned int;
using C = char;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("a.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    U m = 0;
    U f = 2;
    U r = 0;
    for (U i = n; i--;) {
      C c;
      cin >> c;
      if (c == '0') {
        if (f == 1)
          r++;
        if (m++)
          r += 2;
        f = 0;
      } else {
        f++;
        m = 0;
      }
    }
    printf("%u\n", r);
  }
}