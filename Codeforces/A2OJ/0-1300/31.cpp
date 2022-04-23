#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("31.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  const U x = n + 1;
  U total = 0;
  for (U i = n; i--;) {
    U f;
    cin >> f; 
    total += f;
  }
  U result = 0;
  for (U i = 5; i--;)
    result += !!((total + i) % x);
  printf("%u\n", result);
  return 0;
}