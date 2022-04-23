#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;

I as[1000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("36.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U i = 0; i < n; i++)
    cin >> as[i];
  auto l = as[0];
  I min_diff = abs(l - as[n - 1]);
  U a_result = n;
  U b_result = 1;
  for (U i = 1; i < n; i++) {
    const auto a = as[i];
    const I diff = abs(a - l);
    if (diff < min_diff) {
      min_diff = diff;
      a_result = i;
      b_result = i + 1;
    }
    l = a;
  }
  printf("%u %u\n", a_result, b_result);
  return 0;
}