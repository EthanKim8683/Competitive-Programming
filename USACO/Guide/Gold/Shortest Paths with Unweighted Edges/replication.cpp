#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 1000;

C cels[N][N + 1];
I diss[N][N];
I sizs[N][N];
B viss1[N][N];
B viss2[N][N];
B viss3[N][N];
queue<tuple<I, I, I>> que1;
queue<tuple<I, I, I, I>> que2;
priority_queue<tuple<I, I, I>> que3;
I n, d;

B bnd(I i, I j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

void pus1(I i, I j, I dis) {
  if (!bnd(i, j) || viss1[i][j])
    return;
  viss1[i][j] = true;
  diss[i][j] = dis;
  que1.push({i, j, dis});
}

void pus2(I i, I j, I siz, I tim) {
  if (!bnd(i, j) || viss2[i][j] || cels[i][j] == '#' || siz > diss[i][j])
    return;
  siz += tim / d;
  tim %= d;
  viss2[i][j] = true;
  sizs[i][j] = min(diss[i][j], siz);
  if (siz <= diss[i][j])
    que2.push({i, j, siz, tim});
}

void pus3(I siz, I i, I j) {
  if (!bnd(i, j) || viss3[i][j] || cels[i][j] == '#' || siz < 1)
    return;
  viss3[i][j] = true;
  if (siz > 1)
    que3.push({siz, i, j});
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> d;
  for (I i = 0; i < n; i++)
    cin >> cels[i];
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      if (cels[i][j] == '#')
        pus1(i, j, 0);
  while (!que1.empty()) {
    const auto [i, j, dis] = que1.front();
    que1.pop();
    pus1(i - 1, j, dis + 1);
    pus1(i + 1, j, dis + 1);
    pus1(i, j - 1, dis + 1);
    pus1(i, j + 1, dis + 1);
  }
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      if (cels[i][j] == 'S')
        pus2(i, j, 1, 0);
  while (!que2.empty()) {
    const auto [i, j, siz, tim] = que2.front();
    que2.pop();
    pus2(i - 1, j, siz, tim + 1);
    pus2(i + 1, j, siz, tim + 1);
    pus2(i, j - 1, siz, tim + 1);
    pus2(i, j + 1, siz, tim + 1);
  }
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      if (viss2[i][j])
        pus3(sizs[i][j], i, j);
  while (!que3.empty()) {
    const auto [siz, i, j] = que3.top();
    que3.pop();
    pus3(siz - 1, i - 1, j);
    pus3(siz - 1, i + 1, j);
    pus3(siz - 1, i, j - 1);
    pus3(siz - 1, i, j + 1);
  }
  I res = 0;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      res += viss3[i][j];
  printf("%i\n", res);
  return 0;
}