#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using C = char;

const I N = 1000;
const I M = 1000;
const Lli MAX = 1e18;

Lli dp[N + 1][M + 1];
C f_str[N + 1];
C b_str[M + 1];
pair<I, I> f_poss[N + 1];
pair<I, I> b_poss[M + 1];

Lli sqr(Lli i) {
  return i * i;
}

Lli cst(pair<I, I>& f, pair<I, I>& b) {
  return sqr(f.first - b.first) + sqr(f.second - b.second);
}

void mov(C c, I& x, I& y) {
  switch (c) {
    case 'N':
      y++;
      break;
    case 'E':
      x++;
      break;
    case 'S':
      y--;
      break;
    case 'W':
      x--;
      break;
  }
}

I main(void) {
  freopen("radio.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("radio.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  I fx, fy;
  cin >> fx >> fy;
  I bx, by;
  cin >> bx >> by;
  cin >> f_str;
  cin >> b_str;
  f_poss[0] = {fx, fy};
  b_poss[0] = {bx, by};
  for (I i = 0; i < n; i++) {
    mov(f_str[i], fx, fy);
    f_poss[i + 1] = {fx, fy};
  }
  for (I i = 0; i < m; i++) {
    mov(b_str[i], bx, by);
    b_poss[i + 1] = {bx, by};
  }
  for (I i = 0; i <= n; i++)
    fill_n(dp[i], m + 1, MAX);
  dp[0][0] = 0;
  for (I i = 0; i <= n; i++) {
    for (I j = 0; j <= m; j++) {
      if (i + 1 <= n)
        dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + cst(f_poss[i + 1], b_poss[j]));
      if (j + 1 <= m)
        dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + cst(f_poss[i], b_poss[j + 1]));
      if (i + 1 <= n && j + 1 <= m)
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + cst(f_poss[i + 1], b_poss[j + 1]));
    }
  }
  printf("%lli\n", dp[n][m]);
  return 0;
}