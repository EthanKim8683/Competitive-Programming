#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U as[50];
U bs[50];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("45.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U i = n; i--;)
    cin >> as[i];
  U m;
  cin >> m;
  for (U i = m; i--;)
    cin >> bs[i];
  U max_ratio = 0;
  U max_count = 0;
  for (U i = n; i--;) {
    const auto a = as[i];
    for (U j = m; j--;) {
      const auto b = bs[j];
      const U ratio = b / a;
      if (ratio * a == b) {
        if (ratio > max_ratio) {
          max_ratio = ratio;
          max_count = 1;
        } else if (ratio == max_ratio)
          max_count++;
      }
    }
  }
  printf("%u\n", max_count);
  return 0;
}