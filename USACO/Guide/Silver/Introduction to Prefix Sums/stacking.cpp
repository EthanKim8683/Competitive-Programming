#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;

I ps[1000000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("stacking.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  while (k--) {
    U a, b;
    cin >> a >> b;
    ps[a - 1]++;
    ps[b]--;
  }
  U sum = 0;
  for (U i = 0; i < n; i++) {
    sum += ps[i];
    ps[i] = sum;
  }
  const U h = n / 2;
  nth_element(ps, ps + h, ps + n);
  printf("%i\n", ps[h]);
  return 0;
}