#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("96.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  I x, y;
  U n;
  cin >> x >> y >> n;
  I result;
  switch ((n - 1) % 6) {
    case 0:
      result = x;
      break;
    case 1:
      result = y;
      break;
    case 2:
      result = y - x;
      break;
    case 3:
      result = -x;
      break;
    case 4:
      result = -y;
      break;
    case 5:
      result = x - y;
      break;
  }
  result %= 1000000007;
  if (result < 0)
    result += 1000000007;
  printf("%i\n", result);
  return 0;
}