#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 100;

B viss[N][N];
vector<pair<I, I>> swts[N][N];
B lits[N][N];
I n;

B bnd(I i, I j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

void dfs(I i, I j) {

}

I main(void) {
#ifndef ETHANKIM8683
  freopen("lightson.in", "r", stdin);
  freopen("lightson.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I x, y, a, b;
    cin >> x >> y >> a >> b;
    swts[x - 1][y - 1].push_back({a - 1, b - 1});
  }
  return 0;
}