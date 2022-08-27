#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

I begs[N];
tuple<I, I, I> rngs[N];
Lli dp[N + 1];
I n;

I ind(I val) {
  return upper_bound(begs, begs + n, val) - begs;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, b, p;
    cin >> a >> b >> p;
    rngs[i] = {a, b, p};
    begs[i] = a;
  }
  sort(begs, begs + n);
  sort(rngs, rngs + n);
  for (I i = 0; i < n; i++) {
    const auto [a, b, p] = rngs[i];
    const I j = ind(b);
    dp[j] = max(dp[j], dp[i] + p);
    dp[i + 1] = max(dp[i + 1], dp[i]);
  }
  printf("%lli\n", dp[n]);
  return 0;
}