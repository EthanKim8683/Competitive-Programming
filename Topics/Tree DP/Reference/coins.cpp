#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

// 1. current node
// 2. x out, x in
Lli dp[N][2];
I c_arr[N];
vector<I> adjs[N];

void dfs(I a, I p = -1) {
  dp[a][0] = 0;
  dp[a][1] = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      dp[a][0] += max(dp[b][0], dp[b][1]);
      dp[a][1] += dp[b][0];
    }
  }
  dp[a][1] += c_arr[a];
}

Lli slv() {
  dfs(0);
  return max(dp[0][0], dp[0][1]);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> c_arr[i];
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