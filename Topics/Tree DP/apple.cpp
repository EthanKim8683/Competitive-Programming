#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;

const I N = 100;
const I Q = N - 1;

vector<pair<I, I>> adjs[N];
I dp[N][Q + 1];
I q;

void dfs(I a, I p = -1) {
  for (const auto [b, app] : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      for (I i = q; i >= 0; i--)
        for (I j = q - i - 1; j >= 0; j--)
          dp[a][i + j + 1] = max(dp[a][i + j + 1], dp[a][i] + dp[b][j] + app);
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> q;
  for (I i = 0; i < n - 1; i++) {
    I a, b, app;
    cin >> a >> b >> app;
    a--;
    b--;
    adjs[a].push_back({b, app});
    adjs[b].push_back({a, app});
  }
  dfs(0);
  printf("%i\n", dp[0][q]);
  return 0;
}