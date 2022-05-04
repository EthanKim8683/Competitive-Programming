#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

map<I, Lli> ps;

I main(void) {
#ifdef ETHANKIM8683
  freopen("580b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, d;
  cin >> n >> d;
  for (I i = n; i--;) {
    I m, s;
    cin >> m >> s;
    ps[m] += s;
  }
  Lli sum = 0;
  for (auto& [m, p] : ps) {
    const Lli tmp = p;
    p = sum;
    sum += tmp;
  }
  ps[2e9 + 1] = sum;
  Lli res = 0;
  for (const auto [m, l] : ps) {
    auto it = ps.upper_bound(m + d);
    const auto u = it->second;
    res = max(res, u - l);
  }
  printf("%lli\n", res);
  return 0;
}