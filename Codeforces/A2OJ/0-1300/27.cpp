#include <iostream>
#include <cstdio>

#define is_upper(c) ((c) >= 'A' && (c) <= 'Z')
#define to_upper(c) ((c) + 'A' - 'a')

using namespace std;

using U = unsigned;
using C = char;

C a_s[101];
C b_s[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("27.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> a_s;
  cin >> b_s;
  U i = 0;
  while (true) {
    auto a_c = a_s[i];
    auto b_c = b_s[i];
    if (!a_c || !b_c)
      break;
    i++;
    if (!is_upper(a_c))
      a_c = to_upper(a_c);
    if (!is_upper(b_c))
      b_c = to_upper(b_c);
    if (a_c > b_c) {
      printf("1");
      return 0;
    } else if (a_c < b_c) {
      printf("-1");
      return 0;
    }
  }
  printf("0");
  return 0;
}