#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;
using C = char;

C line[4];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("29.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  I result = 0;
  while (n--) {
    cin >> line;
    if (line[1] == '+')
      result++;
    else
      result--;
  }
  printf("%i\n", result);
  return 0;
}