#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("19.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U result = 0;
  U total = 0;
  while (n--) {
    U a, b;
    cin >> a >> b;
    total = total - a + b;
    result = max(result, total);
  }
  printf("%u\n", result);
  return 0;
}