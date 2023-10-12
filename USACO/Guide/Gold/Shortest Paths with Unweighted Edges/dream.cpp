#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using C = char;

const I N = 1000;
const I M = 1000;

I cels[N][M];
B viss[N][M][2][5];
queue<tuple<I, I, B, I, I>> que;
I n, m;

void mov(I i, I j, B sml, I dir, I dst) {
  const I k = i + (dir == 0) - (dir == 2);
  const I l = j + (dir == 1) - (dir == 3);
  if (k >= 0 && k < n && l >= 0 && l < m) {
    switch (cels[k][l]) {
      case 0:
        que.push({i, j, sml, 4, dst});
        break;
      case 1:
        que.push({k, l, sml, 4, dst + 1});
        break;
      case 2:
        que.push({k, l, true, 4, dst + 1});
        break;
      case 3:
        if (sml)
          que.push({k, l, true, 4, dst + 1});
        else
          que.push({i, j, false, 4, dst});
        break;
      case 4:
        que.push({k, l, false, dir, dst + 1});
        break;
    }
  } else
    que.push({i, j, sml, 4, dst});
}

I main(void) {
  freopen("dream.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("dream.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < m; j++)
      cin >> cels[i][j];
  que.push({0, 0, false, 4, 0});
  while (!que.empty()) {
    const auto [i, j, sml, dir, dst] = que.front();
    que.pop();
    if (!viss[i][j][sml][dir]) {
      viss[i][j][sml][dir] = true;
      if (i == n - 1 && j == m - 1) {
        printf("%i\n", dst);
        return 0;
      }
      if (dir == 4) {
        mov(i, j, sml, 0, dst);
        mov(i, j, sml, 1, dst);
        mov(i, j, sml, 2, dst);
        mov(i, j, sml, 3, dst);
      } else
        mov(i, j, sml, dir, dst);
    }
  }
  printf("-1\n");
  return 0;
}