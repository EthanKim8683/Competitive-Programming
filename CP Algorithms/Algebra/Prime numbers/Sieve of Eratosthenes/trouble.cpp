#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const Lli N = 1e10;
const I SQTN = 1e5;

vector<Lli> sqrs;
B coms[SQTN + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  for (Lli i = 2; i <= SQTN; i++) {
    if (!coms[i]) {
      sqrs.push_back(i * i);
      for (Lli j = i * i; j <= SQTN; j += i)
        coms[j] = true;
    }
  }
  I t;
  cin >> t;
  while (t--) {
    Lli n, k;
    cin >> n >> k;
    const auto tot = upper_bound(sqrs.begin(), sqrs.end(), n);
    const auto exc = upper_bound(sqrs.begin(), sqrs.end(), k);
    printf("%i %i\n", tot - sqrs.begin(), max((I) (tot - exc), 0));
  }
  return 0;
}