#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

vector<I> adjs[N];
I dp[N][2];
stack<I> stas[N];
I n;

I top(I a) {
  if (stas[a].empty())
    return 0;
  return stas[a].top();
}

void dfs1(I a, I p = -1) {
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs1(b, a);
      dp[a][0] = max(dp[a][0], dp[b][0] + 1);
      stas[a].push(max(top(a), dp[b][0] + 1));
    }
  }
  reverse(adjs[a].begin(), adjs[a].end());
}

void dfs2(I a, I p = -1) {
  I low = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      stas[a].pop();
      dp[b][1] = max(dp[a][1] + 1, max(top(a), low) + 1);
      low = max(low, dp[b][0] + 1);
      dfs2(b, a);
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0);
  dfs2(0);
  for (I i = 0; i < n; i++)
    printf("%i ", max(dp[i][0], dp[i][1]));
  return 0;
}