#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using C = char;

const I N = 5e4;
const I K = 50;

I brds[N];
B coms[K][K];
C lin[K + 1];
B viss[N][K];
queue<tuple<I, I, I>> que;

I main(void) {
#ifdef ETHANKIM8683
  freopen("telephone.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++) {
    I b;
    cin >> b;
    brds[i] = b - 1;
  }
  for (I i = 0; i < k; i++) {
    cin >> lin;
    for (I j = 0; j < k; j++)
      if (lin[j] == '1')
        coms[i][j] = true;
  }
  que.push({0, 0, brds[0]});
  while (!que.empty()) {
    const auto [a, dst, par] = que.front();
    que.pop();
    if (!viss[a][par]) {
      viss[a][par] = true;
      if (coms[par][brds[a]]) {
        if (a == n - 1) {
          printf("%i\n", dst);
          return 0;
        }
        if (a - 1 >= 0)
          que.push({a - 1, dst + 1, brds[a]});
        if (a + 1 < n)
          que.push({a + 1, dst + 1, brds[a]});
      }
      if (a - 1 >= 0)
        que.push({a - 1, dst + 1, par});
      if (a + 1 < n)
        que.push({a + 1, dst + 1, par});
    }
  }
  printf("-1\n");
  return 0;
}