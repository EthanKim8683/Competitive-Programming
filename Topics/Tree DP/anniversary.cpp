#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 6000;

I cons[N];
B viss[N];
vector<I> adjs[N];
vector<I> tops;
I dp[N][2];

void dfs1(I a) {
  if (viss[a])
    return;
  viss[a] = true;
  for (const auto b : adjs[a])
    dfs1(b);
  tops.push_back(a);
}

void dfs2(I a) {
  if (viss[a])
    return;
  viss[a] = true;
  dp[a][1] = cons[a];
  for (const auto b : adjs[a]) {
    dfs2(b);
    dp[a][1] += dp[b][0];
    dp[a][0] += max(dp[b][0], dp[b][1]);
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> cons[i];
  while (true) {
    I l, k;
    cin >> l >> k;
    if (l == 0 && k == 0)
      break;
    adjs[k - 1].push_back(l - 1);
  }
  for (I i = 0; i < n; i++)
    dfs1(i);
  reverse(tops.begin(), tops.end());
  fill_n(viss, n, false);
  I res = 0;
  for (I i = 0; i < n; i++) {
    const I a = tops[i];
    if (!viss[a]) {
      dfs2(a);
      res += max(dp[a][0], dp[a][1]);
    }
  }
  printf("%i\n", res);
  return 0;
}