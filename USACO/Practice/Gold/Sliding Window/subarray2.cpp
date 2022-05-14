#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

I x_arr[N];
Lli ps[N + 1];
multiset<Lli> vals;

I main(void) {
#ifdef ETHANKIM8683
  freopen("subarray.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, a, b;
  cin >> n >> a >> b;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  for (I i = 0; i < n; i++)
    ps[i + 1] = ps[i] + x_arr[i];
  for (I i = a; i <= b; i++)
    vals.insert(ps[i]);
  Lli res = *vals.rbegin();
  for (I i = 1; i + a - 1 < n; i++) {
    vals.erase(vals.find(ps[i + a - 1]));
    if (i + b <= n)
      vals.insert(ps[i + b]);
    res = max(res, *vals.rbegin() - ps[i]);
  }
  printf("%lli\n", res);
  return 0;
}