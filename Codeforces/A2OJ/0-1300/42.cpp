#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[11];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("42.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  U i = 0;
  C l;
  while (true) {
    const auto c = s[i];
    if (!c)
      break;
    U count = 1;
    while (++i && s[i] == c)
      count++;
    switch (c) {
      case '1':
        break;
      case '4':
        if (l == '1' && count <= 2)
          break;
      default:
        printf("NO");
        return 0;
    }
    l = c;
  }
  printf("YES");
  return 0;
}