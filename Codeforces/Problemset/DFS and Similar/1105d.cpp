#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <tuple>

#define N 1000

using namespace std;

using I = int;
using C = char;
using B = bool;

I cells[N][N];
I s_arr[N];
queue<tuple<I, I, I>> players[9];
queue<tuple<I, I, I>> temps;
I result[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1105d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, p;
  cin >> n >> m >> p;
  for (I i = 0; i < p; i++)
    cin >> s_arr[i];
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      C s;
      cin >> s;
      switch (s) {
        case '#':
          cells[i][j] = -1;
          break;
        case '.':
          break;
        default: {
          const I player = s - '0';
          const I index = player - 1;
          players[index].emplace(s_arr[index], i, j);
          cells[i][j] = player;
          break;
        }
      }
    }
  }
  I index = 0;
  I skips = 0;
  while (skips < p) {
    auto& states = players[index];
    if (states.size()) {
      skips = 0;
      const I player = index + 1;
      const I s = s_arr[index];
      do {
        const auto [x, i, j] = states.front();
        states.pop();
        const I d = x - 1;
        const auto expand = [&](I i, I j) {
          if (!cells[i][j]) {
            cells[i][j] = player;
            if (d)
              states.emplace(d, i, j);
            else
              temps.emplace(s, i, j);
          }
        };
        if (i > 0)
          expand(i - 1, j);
        if (i < n - 1)
          expand(i + 1, j);
        if (j > 0)
          expand(i, j - 1);
        if (j < m - 1)
          expand(i, j + 1);
      } while (states.size());
      states.swap(temps);
    } else
      skips++;
    index = (index + 1) % p;
  }
  for (I i = n; i--;) {
    for (I j = m; j--;) {
      const auto cell = cells[i][j];
      if (cell > 0)
        result[cell - 1]++;
    }
  }
  for (I i = 0; i < p; i++)
    printf("%i ", result[i]);
  return 0;
}