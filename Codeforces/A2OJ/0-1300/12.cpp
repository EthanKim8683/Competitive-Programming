#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C a_s[101];
C b_s[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("12.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> a_s;
  cin >> b_s;
  U i = 0;
  while (true) {
    const C a = a_s[i];
    const C b = b_s[i];
    if (!a || !b)
      break;
    i++;
    printf("%u", a != b);
  }
  return 0;
}