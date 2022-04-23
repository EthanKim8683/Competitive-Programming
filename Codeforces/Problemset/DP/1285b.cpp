#include <iostream>
#include <cstdio>

#define N 100000

using namespace std;

using I = int;
using Lli = long long int;

Lli ps[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1285b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    Lli sum = 0;
    Lli adel = 0;
    Lli prefix = 0;
    I adel_index = 0;
    I prefix_index = 0;
    for (I i = 1; i <= n; i++) {
      I a;
      cin >> a;
      sum += a;
      ps[i] = sum;
      const Lli temp = sum - prefix;
      if (temp > adel) {
        adel = temp;
        adel_index = i;
      }
      if (sum <= prefix) {
        prefix = sum;
        prefix_index = i;
      }
    }
    if (adel_index == n && prefix_index == 0)
      adel = max(ps[n] - ps[1], ps[n - 1] - ps[0]);
    if (sum > adel)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}