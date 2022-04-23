#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U days[7];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("34.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U sum = 0;
  for (U i = 0; i < 7; i++) {
    U day;
    cin >> day;
    sum += day;
    days[i] = sum;
  }
  n %= sum;
  if (n) {
    U result = 0;
    while (days[result] < n)
      result++;
    printf("%u\n", result + 1);
  } else {
    U result = 0;
    while (days[result] != sum)
      result++;
    printf("%u\n", result + 1);
  }
  return 0;
}