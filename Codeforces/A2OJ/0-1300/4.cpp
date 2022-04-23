#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[201];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("4.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  U i = 0;
  while (true) {
    const auto a = s[i];
    if (!a)
      return 0;
    i++;
    switch (a) {
      case '.':
        printf("0");
        break;
      case '-':;
        const auto b = s[i];
        if (!b)
          return 0;
        i++;
        switch (b) {
          case '.':
            printf("1");
            break;
          case '-':
            printf("2");
            break;
        }
        break;
    }
  }
  return 0;
}