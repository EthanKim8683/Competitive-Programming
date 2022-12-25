#include <iostream>
#include <cstdio>
#include <algorithm>  
#include <vector>
#include <numeric>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const I X = 1e4;
const I Y = 1e4;
const Lli MOD = 1e9 + 7;

pair<I, I> psts[N];
vector<I> x_vals[X + X + 1];
vector<I> y_vals[Y + Y + 1];
vector<Lli> x_sums[X + X + 1];
vector<Lli> y_sums[Y + Y + 1];

I x_ind(I x, I y) {
  return lower_bound(x_vals[x].begin(), x_vals[x].end(), y) - x_vals[x].begin();
}

I y_ind(I x, I y) {
  return lower_bound(y_vals[y].begin(), y_vals[y].end(), x) - y_vals[y].begin();
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("triangles.in", "r", stdin);
  freopen("triangles.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    x += X;
    y += Y;
    psts[i] = {x, y};
    x_vals[x].push_back(y);
    y_vals[y].push_back(x);
  }
  for (I i = X - X; i <= X + X; i++) {
    if (!x_vals[i].empty()) {
      sort(x_vals[i].begin(), x_vals[i].end());
      const I len = x_vals[i].size();
      Lli sum = 0;
      for (I j = 1; j < len; j++)
        (sum += x_vals[i][j] - x_vals[i][0]) %= MOD;
      x_sums[i].push_back(sum);
      for (I j = 1; j < len; j++) {
        const I bef = j;
        const I aft = len - j;
        const I chg = x_vals[i][j] - x_vals[i][j - 1];
        x_sums[i].push_back((x_sums[i].back() + bef * chg - aft * chg) % MOD);
      }
    }
  }
  for (I i = Y - Y; i <= Y + Y; i++) {
    if (!y_vals[i].empty()) {
      sort(y_vals[i].begin(), y_vals[i].end());
      const I len = y_vals[i].size();
      Lli sum = 0;
      for (I j = 1; j < len; j++)
        (sum += y_vals[i][j] - y_vals[i][0]) %= MOD;
      y_sums[i].push_back(sum);
      for (I j = 1; j < len; j++) {
        const I bef = j;
        const I aft = len - j;
        const I chg = y_vals[i][j] - y_vals[i][j - 1];
        y_sums[i].push_back((y_sums[i].back() + bef * chg - aft * chg) % MOD);
      }
    }
  }
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const auto [x, y] = psts[i];
    (res += x_sums[x][x_ind(x, y)] * y_sums[y][y_ind(x, y)]) %= MOD;
  }
  printf("%lli\n", res);
  return 0;
}