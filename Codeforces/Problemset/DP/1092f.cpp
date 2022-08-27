#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

vector<I> adjs[N];
I a_arr[N];
Lli dp1[N];
Lli dp2[N];
Lli dp3[N];

void dfs1(I a, I p = -1) {
  dp1[a] = a_arr[a];
  dp2[a] = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs1(b, a);
      dp1[a] += dp1[b];
      dp2[a] += dp1[b] + dp2[b];
    }
  }
}

void dfs2(I a, I p = -1) {
  for (const auto b : adjs[a]) {
    if (b != p) {
      dp3[b] = dp3[a];
      dp3[b] += dp1[0] - dp1[a];
      dp3[b] += dp1[a] - dp1[b];
      dp3[b] += dp2[a] - (dp1[b] + dp2[b]);
      dfs2(b, a);
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
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
  Lli res = 0;
  for (I i = 0; i < n; i++)
    res = max(res, dp2[i] + dp3[i]);
  printf("%lli\n", res);
  return 0;
}