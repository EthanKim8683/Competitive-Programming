#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

using U = unsigned;

U as[100000];
U bs[100000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("98.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U i = 0; i < n; i++)
    cin >> as[i];
  memcpy(bs, as, n * sizeof(U));
  sort(as, as + n);
  U i_min = -1;
  U i_max = 0;
  for (U i = n; i--;) {
    if (as[i] != bs[i]) {
      i_min = min(i_min, i);
      i_max = max(i_max, i);
    }
  }
  if (i_min != -1) {
    U o = i_max;
    for (U i = i_min; i <= i_max; i++) {
      if (as[i] != bs[o]) {
        printf("no");
        return 0;
      }
      o--;
    }
    printf("yes\n%u %u", i_min + 1, i_max + 1);
  } else
    printf("yes\n1 1");
  return 0;
}