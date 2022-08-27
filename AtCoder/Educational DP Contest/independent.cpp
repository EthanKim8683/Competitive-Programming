#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const Lli MOD = 1e9 + 7;

vector<I> adjs[N];
Lli dp[N][2];

void dfs(I a, I p = -1) {
  dp[a][0] = 1;
  dp[a][1] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      (dp[a][0] *= dp[b][1]) %= MOD;
      (dp[a][1] *= dp[b][0] + dp[b][1]) %= MOD;
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n - 1; i++) {
    I x, y;
    cin >> x >> y;
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs(0);
  printf("%lli\n", (dp[0][0] + dp[0][1]) % MOD);
  return 0;
}