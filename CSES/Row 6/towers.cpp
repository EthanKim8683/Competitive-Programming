#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e6;
const Lli MOD = 1e9 + 7;

// current height
// [ ][ ], [    ]
Lli dp[N + 1][2];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  dp[1][0] = 1;
  dp[1][1] = 1;
  for (I i = 0; i < N; i++) {
    // [EEEE] from [    ]
    (dp[i + 1][1] += dp[i][1]) %= MOD;
    // [N][N] from [    ]
    (dp[i + 1][0] += dp[i][1]) %= MOD;
    // [NNNN] from [    ]
    (dp[i + 1][1] += dp[i][1]) %= MOD;
    // [E][E] from [ ][ ]
    (dp[i + 1][0] += dp[i][0]) %= MOD;
    // [E][N] from [ ][ ]
    (dp[i + 1][0] += dp[i][0]) %= MOD;
    // [N][E] from [ ][ ]
    (dp[i + 1][0] += dp[i][0]) %= MOD;
    // [N][N] from [ ][ ]
    (dp[i + 1][0] += dp[i][0]) %= MOD;
    // [NNNN] from [ ][ ]
    (dp[i + 1][1] += dp[i][0]) %= MOD;
  }
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    printf("%lli\n", (dp[n][0] + dp[n][1]) % MOD);
  }
  return 0;
}