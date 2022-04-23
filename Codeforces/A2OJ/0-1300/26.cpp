#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("26.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  U i = 0;
  while (true) {
    const auto c = s[i];
    if (!c)
      break;
    i++;
    switch (c) {
      case 'H':
      case 'Q':
      case '9':
        printf("YES\n");
        return 0;
    }
  }
  printf("NO\n");
  return 0;
}