#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U divisors[1000000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("counting.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U d = 1; d <= 1000000; d++)
    for (U i = d - 1; i < 1000000; i += d)
      divisors[i]++;
  while (n--) {
    U x;
    cin >> x;
    printf("%u\n", divisors[x - 1]);
  }
  return 0;
}