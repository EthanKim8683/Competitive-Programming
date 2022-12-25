#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using I = int;
using C = char;
using S = string;
using B = bool;

const I N = 1000;
const I M = 1000;

I cels[N][M];
I dsts[N][M];
C movs[N][M];
C ress[N * M + 1];
queue<tuple<C, I, I>> que;

I main(void) {
#ifdef ETHANKIM8683
  freopen("monsters.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  I a_i, a_j;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      C c;
      cin >> c;
      switch (c) {
        case 'A':
          a_i = i;
          a_j = j;
          break;
        case 'M':
          que.push({'M', i, j});
          break;
        default:
          cels[i][j] = c == '#';
          break;
      }
    }
  }
  que.push({'A', a_i, a_j});
  while (!que.empty()) {
    const auto [t, i, j] = que.front();
    que.pop();
    if (t == 'M') {
      if (cels[i][j] != 1) {
        cels[i][j] = 1;
        if (i - 1 >= 0 && cels[i - 1][j] != 1)
          que.push({'M', i - 1, j});
        if (i + 1 < n && cels[i + 1][j] != 1)
          que.push({'M', i + 1, j});
        if (j - 1 >= 0 && cels[i][j - 1] != 1)
          que.push({'M', i, j - 1});
        if (j + 1 < m && cels[i][j + 1] != 1)
          que.push({'M', i, j + 1});
      }
    } else {
      if (cels[i][j] == 0) {
        cels[i][j] = 2;
        const auto dst = dsts[i][j];
        if (i - 1 < 0 || i + 1 >= n || j - 1 < 0 || j + 1 >= m) {
          printf("YES\n%i\n", dst);
          I k = i;
          I l = j;
          for (I o = dst - 1; o >= 0; o--) {
            const auto mov = movs[k][l];
            ress[o] = mov;
            k += (mov == 'U') - (mov == 'D');
            l += (mov == 'L') - (mov == 'R');
          }
          printf("%s\n", ress);
          return 0;
        }
        if (cels[i - 1][j] == 0) {
          que.push({'A', i - 1, j});
          dsts[i - 1][j] = dst + 1;
          movs[i - 1][j] = 'U';
        }
        if (cels[i + 1][j] == 0) {
          que.push({'A', i + 1, j});
          dsts[i + 1][j] = dst + 1;
          movs[i + 1][j] = 'D';
        }
        if (cels[i][j - 1] == 0) {
          que.push({'A', i, j - 1});
          dsts[i][j - 1] = dst + 1;
          movs[i][j - 1] = 'L';
        }
        if (cels[i][j + 1] == 0) {
          que.push({'A', i, j + 1});
          dsts[i][j + 1] = dst + 1;
          movs[i][j + 1] = 'R';
        }
      }
    }
  }
  printf("NO\n");
  return 0;
}