#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e6;
const I L = 3;

I vals[N];
I a_arr[N];
Lli fens[L + 1][N + 1];
I n;

I cps(I val) {
  return n - 1 - (lower_bound(vals, vals + n, val) - vals);
}

void upd(Lli fens[], I i, Lli val) {
  for (i++; i <= n; i += i & -i)
    fens[i] += val;
}

Lli qry(Lli fens[], I i) {
  Lli res = 0;
  for (; i > 0; i -= i & -i)
    res += fens[i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  copy_n(a_arr, n, vals);
  sort(vals, vals + n);
  for (I i = 0; i < n; i++) {
    const I a = cps(a_arr[i]);
    for (I j = L - 1; j >= 1; j--)
      upd(fens[j + 1], a, qry(fens[j], a));
    upd(fens[1], a, 1);
  }
  printf("%lli\n", qry(fens[L], n));
  return 0;
}