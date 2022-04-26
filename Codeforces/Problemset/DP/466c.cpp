#include <iostream>
#include <cstdio>
#include <unordered_set>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 5e5;

Lli ps[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("466c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli sum = 0;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    sum += a;
    ps[i] = sum;
  }
  if (sum % 3 != 0) {
    printf("0");
    return 0;
  }
  const Lli thr = sum / 3;
  const Lli tar = thr * 2;
  I tot = 0;
  for (I i = 0; i < n - 1; i++)
    tot += ps[i] == tar;
  Lli res = 0;
  I l = 0;
  while (l < n - 2) {
    while (l < n - 2 && ps[l] != thr) {
      tot -= ps[l] == tar;
      l++;
    }
    if (l < n - 2) {
      tot -= ps[l] == tar;
      res += tot;
      l++;
    }
  }
  printf("%lli", res);
  return 0;
}