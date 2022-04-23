#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using C = char;
using B = bool;

C s[201];
C wub[] = "WUB";

int main(void) {
#if defined(ETHANKIM8683)
  freopen("49.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  U index = 0;
  while (true) {
    const B start = !index;
    U length = 0;
    B space = false;
    while (true) {
      const auto c = s[index + length];
      if (!c)
        break;
      if (c != wub[length])
        break;
      length++;
      if (length >= 3) {
        space = true;
        index += 3;
        length = 0;
      }
    }
    if (space && !start)
      printf(" ");
    const auto c = s[index];
    if (!c)
      break;
    printf("%c", c);
    index++;
  }
  return 0;
}