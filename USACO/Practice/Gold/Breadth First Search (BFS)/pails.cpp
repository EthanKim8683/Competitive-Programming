#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using I = int;
using B = bool;

const I MAX = 1e9;
const I X = 100;
const I Y = 100;

queue<tuple<I, I, I>> que;
B viss[X + 1][Y + 1];

I main(void) {
  freopen("pails.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("pails.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I x, y, k, m;
  cin >> x >> y >> k >> m;
  que.push({0, 0, 0});
  I res = MAX;
  while (!que.empty()) {
    const auto [dep, i, j] = que.front();
    que.pop();
    if (!viss[i][j]) {
      viss[i][j] = true;
      res = min(res, abs(m - (i + j)));
      if (dep + 1 <= k) {
        if (i < x && !viss[x][j])
          que.push({dep + 1, x, j});
        if (j < y && !viss[i][y])
          que.push({dep + 1, i, y});
        if (i > 0 && !viss[0][j])
          que.push({dep + 1, 0, j});
        if (j > 0 && !viss[i][0])
          que.push({dep + 1, i, 0});
        if (i > 0 && j < y) {
          const I mov = min(i, y - j);
          if (!viss[i - mov][j + mov])
            que.push({dep + 1, i - mov, j + mov});
        }
        if (j > 0 && i < x) {
          const I mov = min(x - i, j);
          if (!viss[i + mov][j - mov])
            que.push({dep + 1, i + mov, j - mov});
        }
      }
    }
  }
  printf("%i\n", res);
  return 0;
}