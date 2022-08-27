#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>

using namespace std;

using I = int;
using Lli = long long int;

const I K = 10000;
const I L = 10;

unordered_map<I, unordered_map<I, Lli>> dp[L + 1][2];
I pows[L];

void ini() {
  I pow = 1;
  for (I i = 0; i < L; i++) {
    pows[i] = pow;
    pow *= 10;
  }
}

I dgt(I val, I dgt) {
  return val / pows[dgt] % 10;
}

I len(I val) {
  if (val == 0)
    return 0;
  I l = 0;
  I r = L - 1;
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (val >= pows[m])
      l = m;
    else
      r = m - 1;
  }
  return l + 1;
}

I sum(I val) {
  I res = 0;
  for (I i = 0; i < L; i++) {
    res += val % 10;
    val /= 10;
  }
  return res;
}

Lli slv(I upp, I fac) {
  // sums greater than 82 impossible on [1, 2 ^ 31)
  if (fac > 82)
    return 0;
  upp /= fac;
  const I l = len(upp);
  for (I i = 0; i <= l; i++) {
    dp[i][1].clear();
    dp[i][0].clear();
  }
  dp[0][1][0][0] = 1;
  for (I i = 0; i < l; i++) {
    const I lim = dgt(upp, i);
    // add confirmed digits to total, maintain carry
    for (const auto& [tot, tmp] : dp[i][1])
      for (const auto [cry, cnt] : tmp)
        for (I j = 0; j <= 9; j++)
          dp[i + 1][j <= lim][tot + (cry + j * fac) % 10][(cry + j * fac) / 10] += cnt;
    for (const auto& [tot, tmp] : dp[i][0])
      for (const auto [cry, cnt] : tmp)
        for (I j = 0; j <= 9; j++)
          dp[i + 1][j < lim][tot + (cry + j * fac) % 10][(cry + j * fac) / 10] += cnt;
  }
  // if total divisible by fac, add count to result
  Lli res = 0;
  for (const auto& [tot, tmp] : dp[l][1])
    for (const auto [cry, cnt] : tmp)
      if ((tot + sum(cry)) % fac == 0)
        res += cnt;
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  ini();
  I t;
  cin >> t;
  for (I i = 1; i <= t; i++) {
    I a, b, k;
    cin >> a >> b >> k;
    printf("Case %i: %lli\n", i, slv(b, k) - slv(a - 1, k));
  }
  return 0;
}