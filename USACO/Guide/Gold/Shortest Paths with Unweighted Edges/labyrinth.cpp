#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

using I = int;
using C = char;

const I N = 1000;
const I M = 1000;

C tmp[M + 1];
I dsts[N][M];
I dirs[N][M];
C ress[N * M];
queue<pair<I, I>> stts;

I main(void) {
#ifdef ETHANKIM8683
  freopen("labyrinth.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  I a_i, a_j, b_i, b_j;
  for (I i = 0; i < n; i++) {
    cin >> tmp;
    for (I j = 0; j < m; j++) {
      switch (tmp[j]) {
        case '#':
          dsts[i][j] = 1e9;
          break;
        case 'A':
          a_i = i;
          a_j = j;
          break;
        case 'B':
          b_i = i;
          b_j = j;
          break;
      }
    }
  }
  stts.emplace(a_i, a_j);
  dsts[a_i][a_j] = 1;
  while (!stts.empty()) {
    auto [i, j] = stts.front();
    stts.pop();
    auto dst = dsts[i][j];
    if (i == b_i && j == b_j) {
      dst--;
      for (I l = dst; l--;) {
        switch (dirs[i][j]) {
          case 0:
            ress[l] = 'U';
            i++;
            break;
          case 1:
            ress[l] = 'D';
            i--;
            break;
          case 2:
            ress[l] = 'L';
            j++;
            break;
          case 3:
            ress[l] = 'R';
            j--;
            break;
        }
      }
      printf("YES\n%i\n%s\n", dst, ress);
      return 0;
    }
    dst++;
    if (i - 1 >= 0 && !dsts[i - 1][j]) {
      dsts[i - 1][j] = dst;
      dirs[i - 1][j] = 0;
      stts.emplace(i - 1, j);
    }
    if (i + 1 < n && !dsts[i + 1][j]) {
      dsts[i + 1][j] = dst;
      dirs[i + 1][j] = 1;
      stts.emplace(i + 1, j);
    }
    if (j - 1 >= 0 && !dsts[i][j - 1]) {
      dsts[i][j - 1] = dst;
      dirs[i][j - 1] = 2;
      stts.emplace(i, j - 1);
    }
    if (j + 1 < m && !dsts[i][j + 1]) {
      dsts[i][j + 1] = dst;
      dirs[i][j + 1] = 3;
      stts.emplace(i, j + 1);
    }
  }
  printf("NO\n");
  return 0;
}