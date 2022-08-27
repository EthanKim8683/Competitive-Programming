#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 1e5;
const Lli MOD = 1e9 + 7;

Lli dp[N][2];
B x_arr[N];
vector<I> adjs[N];

Lli pow(Lli x, Lli y) {
  x %= MOD;
  Lli res = 1;
  while (y) {
    if (y & 1)
      (res *= x) %= MOD;
    (x *= x) %= MOD;
    y >>= 1;
  }
  return res;
}

Lli mdv(Lli a, Lli b) {
  return a * pow(b, MOD - 2) % MOD;
}

void dfs(I a) {
  if (x_arr[a]) {
    dp[a][1] = 1;
    for (const auto b : adjs[a]) {
      dfs(b);
      (dp[a][1] *= dp[b][0] + dp[b][1]) %= MOD;
    }
  } else {
    dp[a][0] = 1;
    for (const auto b : adjs[a]) {
      dfs(b);
      (dp[a][0] *= dp[b][0] + dp[b][1]) %= MOD;
    }
    for (const auto b : adjs[a])
      (dp[a][1] += dp[b][1] * mdv(dp[a][0], dp[b][0] + dp[b][1])) %= MOD;
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 1; i < n; i++) {
    I p;
    cin >> p;
    adjs[p].push_back(i);
  }
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  dfs(0);
  printf("%lli\n", dp[0][1]);
  return 0;
}