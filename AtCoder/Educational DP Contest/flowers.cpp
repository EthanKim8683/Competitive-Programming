#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

I h_arr[N];
I a_arr[N];
Lli segs[2 * N];
I n;

void upd(I i, Lli val) {
  for (segs[i += n] = val; i > 1; i >>= 1)
    segs[i >> 1] = max(segs[i], segs[i ^ 1]);
}

Lli qry(I l, I r) {
  Lli res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res = max(res, segs[l++]);
    if (r & 1)
      res = max(res, segs[--r]);
  }
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    I h;
    cin >> h;
    h_arr[i] = h - 1;
  }
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++) {
    const I h = h_arr[i];
    upd(h, qry(0, h) + a_arr[i]);
  }
  printf("%lli\n", qry(0, n));
  return 0;
}