#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;
const I M = 100000;
const I R = 100000;

Lli cows[N];
pair<Lli, Lli> strs[M];
Lli frms[R];
Lli vals[N];

I main(void) {
  freopen("rental.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("rental.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, r;
  cin >> n >> m >> r;
  for (I i = 0; i < n; i++)
    cin >> cows[i];
  for (I i = 0; i < m; i++) {
    I q, p;
    cin >> q >> p;
    strs[i] = {p, q};
  }
  for (I i = 0; i < r; i++)
    cin >> frms[i];
  sort(cows, cows + n, greater<I>());
  sort(strs, strs + m, greater<pair<I, I>>());
  sort(frms, frms + r);
  I cow_ind = 0;
  I str_ind = 0;
  Lli cow_tot = 0;
  Lli str_tot = 0;
  while (cow_ind < n && str_ind < m) {
    const auto cow = cows[cow_ind];
    const auto [cst, gal] = strs[str_ind];
    const I dif = min(cow, gal);
    vals[cow_ind] += dif * cst;
    cow_ind += (cows[cow_ind] -= dif) == 0;
    str_ind += (strs[str_ind].second -= dif) == 0;
  }
  cow_ind = n;
  I frm_ind = r;
  while (--cow_ind >= 0 && --frm_ind >= 0)
    vals[cow_ind] = max(vals[cow_ind], frms[frm_ind]);
  Lli res = 0;
  for (I i = 0; i < n; i++)
    res += vals[i];
  printf("%lli\n", res);
  return 0;
}