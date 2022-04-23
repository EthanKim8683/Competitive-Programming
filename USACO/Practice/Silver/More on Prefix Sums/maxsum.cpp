#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;
using Lli = long long int;

Lli ps[200001];
Lli ps_min[200001];
Lli ps_max[200001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("maxsum.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  Lli sum = 0;
  Lli min_ps = 0;
  for (U i = 1; i <= n; i++) {
    I x;
    cin >> x;
    sum += x;
    ps[i] = sum;
    min_ps = min(min_ps, sum);
    ps_min[i] = min_ps;
  }
  Lli max_ps = ps[n];
  for (U i = n; i--;) {
    ps_max[i] = max_ps;
    max_ps = max(max_ps, ps[i]);
  }
  Lli result = ps_max[0] - ps_min[0];
  for (U i = n; --i;)
    result = max(result, ps_max[i] - ps_min[i]);
  printf("%lli\n", result);
  return 0;
}