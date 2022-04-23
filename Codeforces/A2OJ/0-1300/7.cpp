#include <iostream>
#include <cstdio>

#define is_upper(c) ((c) >= 'A' && (c) <= 'Z')
#define to_upper(c) ((c) + 'A' - 'a')
#define to_lower(c) ((c) + 'a' - 'A')

using namespace std;

using U = unsigned;
using C = char;
using B = bool;

C s[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("7.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  U upper = 0;
  U lower = 0;
  U n = 0;
  while (true) {
    const auto c = s[n];
    if (!c)
      break;
    n++;
    if (is_upper(c))
      upper++;
    else
      lower++;
  }
  B type = upper > lower;
  for (U i = 0; i < n; i++) {
    const auto c = s[i];
    switch (is_upper(c) << 1 | type) {
      case 0b01:
        printf("%c", to_upper(c));
        break;
      case 0b10:
        printf("%c", to_lower(c));
        break;
      default:
        printf("%c", c);
        break;
    }
  }
  return 0;
}