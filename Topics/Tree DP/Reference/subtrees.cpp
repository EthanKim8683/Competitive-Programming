#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

// 1. current node
// 2. x = root, x != root
Lli dp[N][2];
vector<I> adjs[N];

void dfs(I a, I p = -1) {
  dp[a][0] = 0;
  dp[a][1] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      dp[a][1] *= dp[b][1] + 1;
      dp[a][0] += dp[b][1] + dp[b][0];
    }
  }
}

Lli slv() {
  dfs(0);
  return dp[0][0] + dp[0][1];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  printf("%lli\n", slv());
  return 0;
}