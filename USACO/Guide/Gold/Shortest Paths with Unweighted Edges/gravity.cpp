#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using C = char;

const I N = 500;
const I M = 500;

queue<tuple<I, I, I, I>> que;
set<I> objs[M];
B cels[N][M];
B viss[N][M][2];
C lin[N + 1];
I n, m;
I d_i, d_j;

B apl(I& i, I j, I grv) {
  auto it = objs[j].upper_bound(i);
  if (grv == 1) {
    if (it-- == objs[j].begin())
      return false;
    i = *it;
    i += i != d_i || j != d_j;
  } else if (grv == 0) {
    if (it == objs[j].end())
      return false;
    i = *it;
    i -= i != d_i || j != d_j;
  }
  return true;
}

B trv(I i, I j, I grv, I dst) {
  if (!apl(i, j, grv) || viss[i][j][grv])
    return false;
  if (i == d_i && j == d_j)
    return true;
  viss[i][j][grv] = true;
  que.push({i, j, !grv, dst + 1});
  return (j - 1 >= 0 && !cels[i][j - 1] && trv(i, j - 1, grv, dst)) ||
         (j + 1 < m  && !cels[i][j + 1] && trv(i, j + 1, grv, dst));
}

I main(void) {
  freopen("gravity.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("gravity.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (I i = 0; i < n; i++) {
    cin >> lin;
    for (I j = 0; j < m; j++) {
      const auto c = lin[j];
      switch (c) {
        case 'D':
          d_i = i;
          d_j = j;
          objs[j].insert(i);
          break;
        case 'C':
          que.push({i, j, 0, 0});
          break;
        case '#':
          objs[j].insert(i);
          cels[i][j] = true;
          break;
      }
    }
  }
  while (!que.empty()) {
    auto [i, j, grv, dst] = que.front();
    que.pop();
    if (trv(i, j, grv, dst)) {
      printf("%i\n", dst);
      return 0;
    }
  }
  printf("-1\n");
  return 0;
}