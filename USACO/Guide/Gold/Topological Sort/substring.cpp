#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 300000;

I chrs[N];
B viss[N];
vector<I> adjs[N];
vector<I> tops;
I inds[N];
I dp[N][26];

void dfs(I a) {
  if (!viss[a]) {
    viss[a] = true;
    for (const auto b : adjs[a])
      dfs(b);
    tops.push_back(a);
  }
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("substring.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++) {
    C c;
    cin >> c;
    chrs[i] = c - 'a';
  }
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  for (I i = 0; i < n; i++)
    dfs(i);
  reverse(tops.begin(), tops.end());
  for (I i = 0; i < n; i++)
    inds[tops[i]] = i;
  for (I i = 0; i < n; i++) {
    for (const auto b : adjs[i]) {
      if (inds[i] >= inds[b]) {
        printf("-1\n");
        return 0;
      }
    }
  }
  for (I i = 0; i < n; i++) {
    dp[i][chrs[tops[i]]]++;
    for (const auto b : adjs[tops[i]]) {
      const auto j = inds[b];
      for (I k = 0; k < 26; k++)
        dp[j][k] = max(dp[j][k], dp[i][k]);
    }
  }
  I res = 0;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < 26; j++)
      res = max(res, dp[i][j]);
  printf("%i\n", res);
  return 0;
}