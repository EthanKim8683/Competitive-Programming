#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;

const I N = 2e5;
const I MIN = -1e9;

// 1. current node
// 2. edge, no edge
I dp[N][2];
vector<I> adjs[N];

void dfs(I a, I p = -1) {
  dp[a][0] = 0;
  dp[a][1] = 0;
  I edg = MIN;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      edg = max(edg, dp[b][1] + 1 - max(dp[b][0], dp[b][1]));
      dp[a][0] += max(dp[b][0], dp[b][1]);
      dp[a][1] += max(dp[b][0], dp[b][1]);
    }
  }
  if (edg != MIN)
    dp[a][0] += edg;
}

I slv() {
  dfs(0);
  return max(dp[0][0], dp[0][1]);
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
  printf("%i\n", slv());
  return 0;
}