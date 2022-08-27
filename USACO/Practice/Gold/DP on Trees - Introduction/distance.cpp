#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 50000;
const I K = 500;

// 1. current node
// 2. distance
Lli dp[N][K + 1];
vector<I> adjs[N];
Lli res;
I k;

void dfs(I a, I p = -1) {
  dp[a][0] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      for (I i = 0; i < k; i++)
        res += dp[b][i] * dp[a][k - (i + 1)];
      for (I i = 0; i < k; i++)
        dp[a][i + 1] += dp[b][i];
    }
  }
}

Lli slv() {
  res = 0;
  dfs(0);
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> k;
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