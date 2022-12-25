#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

vector<I> adjs[N];
I dp1[N];
Lli dp2[N][2];

void dfs1(I a, I p = -1) {
  dp1[a] = 1;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs1(b, a);
      dp1[a] += dp1[b];
      dp2[a][0] += dp1[b] + dp2[b][0];
    }
  }
}

void dfs2(I a, I p = -1) {
  for (const auto b : adjs[a]) {
    if (b != p) {
      dp2[b][1] += dp1[0] - dp1[b];
      dp2[b][1] += dp2[a][0] - (dp1[b] + dp2[b][0]);
      dp2[b][1] += dp2[a][1];
      dfs2(b, a);
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n - 1; i++) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0);
  dfs2(0);
  Lli res = 0;
  for (I i = 0; i < n; i++)
    res = max(res, dp2[i][0] + dp2[i][1]);
  printf("%lli\n", res + n);
  return 0;
}