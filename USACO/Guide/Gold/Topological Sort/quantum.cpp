#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1000;
const I M = 2000;

vector<I> adjs[2][N];
vector<I> tops[2];
B viss[2][N];
I inds[2][N];
unordered_set<I> dp[2][N];

void dfs(I ind, I a) {
  if (!viss[ind][a]) {
    viss[ind][a] = true;
    for (const auto b : adjs[ind][a])
      dfs(ind, b);
    tops[ind].push_back(a);
  }
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("quantum.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n1, n2, m1, m2;
  cin >> n1 >> n2 >> m1 >> m2;
  for (I i = 0; i < m1; i++) {
    I a, b;
    cin >> a >> b;
    adjs[0][a - 1].push_back(b - 1);
  }
  for (I i = 0; i < m2; i++) {
    I a, b;
    cin >> a >> b;
    adjs[1][a - 1].push_back(b - 1);
  }
  for (I i = 0; i < n1; i++)
    dfs(0, i);
  for (I i = 0; i < n2; i++)
    dfs(1, i);
  reverse(tops[0].begin(), tops[0].end());
  reverse(tops[1].begin(), tops[1].end());
  for (I i = 0; i < n1; i++)
    inds[0][tops[0][i]] = i;
  for (I i = 0; i < n2; i++)
    inds[1][tops[1][i]] = i;
  dp[0][inds[0][0]].insert(0);
  dp[1][inds[1][0]].insert(0);
  for (I i = 0; i < n1; i++)
    for (const auto len : dp[0][i])
      for (const auto b : adjs[0][tops[0][i]])
        dp[0][inds[0][b]].insert(len + 1);
  for (I i = 0; i < n2; i++)
    for (const auto len : dp[1][i])
      for (const auto b : adjs[1][tops[1][i]])
        dp[1][inds[1][b]].insert(len + 1);
  const auto a_pths = dp[0][inds[0][n1 - 1]];
  const auto b_pths = dp[1][inds[1][n2 - 1]];
  I q;
  cin >> q;
  while (q--) {
    I s;
    cin >> s;
    B res = false;
    for (const auto len : a_pths) {
      if (b_pths.find(s - len) != b_pths.end()) {
        res = true;
        break;
      }
    }
    if (res)
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}