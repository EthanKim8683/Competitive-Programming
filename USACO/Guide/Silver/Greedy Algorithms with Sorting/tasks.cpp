#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

pair<I, I> tsks[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, d;
    cin >> a >> d;
    tsks[i] = {a, d};
  }
  sort(tsks, tsks + n);
  Lli res = 0;
  Lli end = 0;
  for (I i = 0; i < n; i++) {
    const auto [a, d] = tsks[i];
    end += a;
    res += d - end;
  }
  printf("%lli\n", res);
  return 0;
}