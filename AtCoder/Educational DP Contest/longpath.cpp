#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<I> adjs[N];
B viss[N];
vector<I> tops;
I dp[N];
I n;

void dfs(I a) {
  if (viss[a])
    return;
  viss[a] = true;
  for (const auto b : adjs[a])
    dfs(b);
  tops.push_back(a);
}

void top() {
  for (I i = 0; i < n; i++)
    dfs(i);
  reverse(tops.begin(), tops.end());
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I x, y;
    cin >> x >> y;
    adjs[y - 1].push_back(x - 1);
  }
  top();
  for (I i = 0; i < n; i++) {
    const I a = tops[i];
    for (const auto b : adjs[a])
      dp[b] = max(dp[b], dp[a] + 1);
  }
  I res = 0;
  for (I i = 0; i < n; i++)
    res = max(res, dp[i]);
  printf("%i\n", res);
  return 0;
}