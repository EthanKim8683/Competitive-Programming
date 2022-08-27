#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;

vector<I> adjs[N];
Lli dp[N][2];
stack<Lli> stas[N];
I m;

void dfs1(I a, I p = -1) {
  stas[a].push(dp[a][0]);
  for (const auto b : adjs[a]) {
    if (b == p)
      continue;
    dfs1(b, a);
    (dp[a][0] *= dp[b][0] + 1) %= m;
    stas[a].push(dp[a][0]);
  }
  reverse(adjs[a].begin(), adjs[a].end());
}

void dfs2(I a, I p = -1) {
  Lli cur = 1;
  for (const auto b : adjs[a]) {
    if (b == p)
      continue;
    stas[a].pop();
    (dp[b][1] *= dp[a][1]) %= m;
    (dp[b][1] *= cur * stas[a].top() % m) %= m;
    (dp[b][1] += 1) %= m;
    (cur *= dp[b][0] + 1) %= m;
    dfs2(b, a);
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> m;
  for (I i = 0; i < n - 1; i++) {
    I x, y;
    cin >> x >> y;
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), 1);
  dfs1(0);
  dfs2(0);
  for (I i = 0; i < n; i++)
    printf("%lli\n", (dp[i][0] * dp[i][1]) % m);
  return 0;
}