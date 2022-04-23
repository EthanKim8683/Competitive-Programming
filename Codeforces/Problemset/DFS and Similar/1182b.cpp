#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;
using C = char;

B grid[500][500];
I counts[500][500];
I h, w;

I count(I i, I j) {
  I count = 0;
  if (grid[i][j]) {
    count++;
    count += i > 0     && grid[i - 1][j];
    count += i < h - 1 && grid[i + 1][j];
    count += j > 0     && grid[i][j - 1];
    count += j < w - 1 && grid[i][j + 1];
  }
  return count;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1182b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> h >> w;
  for (I i = 0; i < h; i++) {
    for (I j = 0; j < w; j++) {
      C c;
      cin >> c;
      grid[i][j] = c == '*';
    }
  }
  for (I i = 0; i < h; i++)
    for (I j = 0; j < w; j++)
      counts[i][j] = count(i, j);
  for (I i = 0; i < h; i++) {
    for (I j = 0; j < w; j++) {
      if (counts[i][j] == 5) {
        for (I t = i - 1; t >= 0 && counts[t][j]; t--)
          counts[t][j] = 0;
        for (I t = i + 1; t < h  && counts[t][j]; t++)
          counts[t][j] = 0;
        for (I t = j - 1; t >= 0 && counts[i][t]; t--)
          counts[i][t] = 0;
        for (I t = j + 1; t < w  && counts[i][t]; t++)
          counts[i][t] = 0;
      }
    }
  }
  I result = 0;
  for (I i = 0; i < h; i++) {
    for (I j = 0; j < w; j++) {
      switch (counts[i][j]) {
        default:
          result++;
        case 5:
          result++;
        case 0:
          break;
      }
    }
  }
  if (result == 1)
    printf("YES");
  else
    printf("NO");
  return 0;
}