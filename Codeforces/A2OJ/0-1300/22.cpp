#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("22.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  while (n--) {
    cin >> s;
    U length = 0;
    while (s[length])
      length++;
    if (length > 10)
      printf("%c%u%c\n", s[0], length - 2, s[length - 1]);
    else
      printf("%s\n", s);
  }
  return 0;
}