#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;
const I LOGN = 17;

I a_arr[N];
I sprs[N][LOGN];
I n;

void asn(I i, I val) {
  sprs[i][0] = val;
}

void bld() {
  for (I i = 1; i < LOGN; i++)
    for (I j = 0, k = 1 << (i - 1); k < n - 1; j++, k++)
      sprs[j][i] = max(sprs[j][i - 1], sprs[k][i - 1]);
}

I qry(I l, I r) {
  const I dis = 31 - __builtin_clz(r - l);
  return max(sprs[l][dis], sprs[r - (1 << dis)][dis]);
}

I upp(I i) {
  return upper_bound(a_arr, a_arr + n, i) - a_arr - 1;
}

I slv(I t, I d) {
  const I k = upp(t);
  I l = 0;
  I r = k;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (d >= qry(m, k))
      r = m;
    else
      l = m + 1;
  }
  return l;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n - 1; i++)
    asn(i, a_arr[i + 1] - a_arr[i]);
  bld();
  I m;
  cin >> m;
  while (m--) {
    I t, d;
    cin >> t >> d;
    printf("%i ", slv(t, d) + 1);
  }
  return 0;
}