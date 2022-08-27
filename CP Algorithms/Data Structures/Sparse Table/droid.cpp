#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 1e5;
const I M = 5;
const I LOGN = 17;

I sprs[M][N][LOGN];
I ress[M];
I n, m, k;

void asn(I i, I j, I val) {
  sprs[j][i][0] = val;
}

void bld() {
  for (I i = 0; i < m; i++)
    for (I j = 1; j < LOGN; j++)
      for (I k = 0, l = 1 << (j - 1); l < n; k++, l++)
        sprs[i][k][j] = max(sprs[i][k][j - 1], sprs[i][l][j - 1]);
}

I qry(I i, I l, I r) {
  const I dis = 31 - __builtin_clz(r - l);
  return max(sprs[i][l][dis], sprs[i][r - (1 << dis)][dis]);
}

I tot(I l, I r) {
  I res = 0;
  for (I i = 0; i < m; i++)
    res += qry(i, l, r);
  return res;
}

I slv(I i) {
  I l = i + 1;
  I r = n;
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (tot(i, m) <= k)
      l = m;
    else
      r = m - 1;
  }
  return l;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m >> k;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      I a;
      cin >> a;
      asn(i, j, a);
    }
  }
  bld();
  I max_len = 0;
  for (I i = 0; i < n; i++) {
    const I end = slv(i);
    const I len = end - i;
    if (tot(i, end) <= k && len > max_len) {
      max_len = len;
      for (I j = 0; j < m; j++)
        ress[j] = qry(j, i, end);
    }
  }
  for (I i = 0; i < m; i++)
    printf("%i ", ress[i]);
  return 0;
}