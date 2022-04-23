#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("38.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U a_min = -1;
  U b_min = -1;
  U a_index;
  for (U i = 1; i <= n; i++) {
    U x;
    cin >> x;
    if (x <= a_min) {
      b_min = a_min;
      a_min = x;
      a_index = i;
    } else if (i < b_min)
      b_min = x;
  }
  if (a_min == b_min)
    printf("Still Rozdil\n");
  else
    printf("%u\n", a_index);
  return 0;
}