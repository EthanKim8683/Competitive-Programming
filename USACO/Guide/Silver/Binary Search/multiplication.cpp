#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

Lli n;

Lli tes(Lli val) {
  Lli low = 0;
  Lli upp = 0;
  Lli mid = 0;
  for (I i = 1; i <= n; i++) {
    const Lli les = min((val - 1) / i, n);
    const Lli mor = n - min(val / i, n);
    low += les;
    upp += mor;
    mid += n - (les + mor);
  }
  if (low < upp) {
    const Lli dif = min(upp - low, mid);
    low += dif;
    mid -= dif;
  }
  if (upp < low) {
    const Lli dif = min(low - upp, mid);
    upp += dif;
    mid -= dif;
  }
  return low - upp;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  Lli l = 1;
  Lli r = n * n;
  while (l <= r) {
    const Lli m = l + (r - l) / 2;
    const Lli dif = tes(m);
    if (dif == 0) {
      printf("%lli\n", m);
      break;
    }
    if (dif < 0)
      l = m + 1;
    else if (dif > 0)
      r = m - 1;
  }
  return 0;
}