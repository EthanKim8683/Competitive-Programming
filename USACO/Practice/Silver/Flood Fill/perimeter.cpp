#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 1000;

C cels[N][N + 1];
B viss[N][N];
I n;

B bnd(I i, I j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

void cmb1(pair<I, I>& a, pair<I, I> b) {
  a.first += b.first;
  a.second += b.second;
}

void cmb2(pair<I, I>& a, pair<I, I> b) {
  const auto [a1, p1] = a;
  const auto [a2, p2] = b;
  if (a1 == -1 && p1 == -1)
    a = b;
  else if (a2 > a1)
    a = b;
  else if (a2 == a1 && p2 < p1)
    a = b;
}

pair<I, I> dfs(I i, I j) {
  if (!bnd(i, j) || cels[i][j] == '.')
    return {0, 1};
  if (viss[i][j])
    return {0, 0};
  viss[i][j] = true;
  pair<I, I> res = {1, 0};
  cmb1(res, dfs(i - 1, j));
  cmb1(res, dfs(i + 1, j));
  cmb1(res, dfs(i, j - 1));
  cmb1(res, dfs(i, j + 1));
  return res;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("perimeter.in", "r", stdin);
  freopen("perimeter.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> cels[i];
  pair<I, I> res = {-1, -1};
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      if (!viss[i][j] && cels[i][j] == '#')
        cmb2(res, dfs(i, j));
  printf("%i %i\n", res.first, res.second);
  return 0;
}