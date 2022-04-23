#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("28.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U result = 0;
  while (n--) {
    U p, v, t;
    cin >> p >> v >> t;
    U sum = p + v + t;
    result += sum >= 2;
  }
  printf("%u\n", result);
  return 0;
}