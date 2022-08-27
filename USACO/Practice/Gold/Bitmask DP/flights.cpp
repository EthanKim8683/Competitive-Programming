#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 20;
const Lli MOD = 1e9 + 7;

vector<I> adjs[N];
Lli dp[1 << N][N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("flights.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  dp[1 << 0][0] = 1;
  for (const auto b : adjs[0])
    dp[(1 << b) | (1 << 0)][b] += 1;
  for (I i = 0; i < (1 << n) - 1; i++)
    if (!(i & (1 << (n - 1))))
      for (I j = 1; j < n - 1; j++)
        if (i & (1 << j))
          for (const auto b : adjs[j])
            if (!(i & (1 << b)))
              dp[i | (1 << b)][b] = (dp[i | (1 << b)][b] + dp[i][j]) % MOD;
  printf("%lli\n", dp[(1 << n) - 1][n - 1]);
  return 0;
}