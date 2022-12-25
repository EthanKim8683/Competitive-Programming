#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using C = char;
using Lli = long long int;

const I N = 5000;
const I K = 5000;
const Lli MOD = 1e9 + 7;

pair<I, I> wrds[N];
Lli dp[K + 1];
Lli cnts[N + 1];
I scms[26];
Lli coms[26];

Lli pow(Lli bse, Lli exp) {
  bse %= MOD;
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      (res *= bse) %= MOD;
    (bse *= bse) %= MOD;
    exp >>= 1;
  }
  return res;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("poetry.in", "r", stdin);
  freopen("poetry.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, k;
  cin >> n >> m >> k;
  for (I i = 0; i < n; i++) {
    I s, c;
    cin >> s >> c;
    wrds[i] = {s, c};
  }
  for (I i = 0; i < m; i++) {
    C e;
    cin >> e;
    scms[e - 'A']++;
  }
  dp[0] = 1;
  for (I i = 0; i < k; i++) {
    if (dp[i] > 0) {
      for (I j = 0; j < n; j++) {
        const auto [s, c] = wrds[j];
        if (i + s == k)
          (cnts[c] += dp[i]) %= MOD;
        else if (i + s < k)
          (dp[i + s] += dp[i]) %= MOD;
      }
    }
  }
  for (I i = 1; i <= N; i++)
    if (cnts[i] > 0)
      for (I j = 0; j < 26; j++)
        if (scms[j] > 0)
          (coms[j] += pow(cnts[i], scms[j])) %= MOD;
  Lli res = 0;
  for (I i = 0; i < 26; i++) {
    if (coms[i] > 0) {
      if (res == 0)
        res = coms[i];
      else
        (res *= coms[i]) %= MOD;
    }
  }
  printf("%lli\n", res);
  return 0;
}