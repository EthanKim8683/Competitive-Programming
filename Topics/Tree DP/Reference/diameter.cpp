#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;

const I N = 2e5;

// 1. current node
I dp[N];
vector<I> adjs[N];
I dia = 0;

void dfs(I a, I p = -1) {
  I rad0 = 0;
  I rad1 = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      if (dp[b] > rad0) {
        rad1 = rad0;
        rad0 = dp[b];
      } else if (dp[b] > rad1)
        rad1 = dp[b];
    }
  }
  dia = max(dia, rad0 + rad1);
  dp[a] = rad0 + 1;
}

I slv() {
  dia = 0;
  dfs(0);
  return dia;
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