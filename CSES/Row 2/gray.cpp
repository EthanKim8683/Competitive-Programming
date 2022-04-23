// start 6:02
// end 6:20
// tries 1

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned int;
using C = char;

C s[17];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("gray.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  memset(s, '0', n);
  printf("%s\n", s);
  for (U i = 1 << n; i--;) {
    const U d = __builtin_ctz(i);
    s[d] = !(s[d] - '0') + '0';
    printf("%s\n", s);
  }
  return 0;
}