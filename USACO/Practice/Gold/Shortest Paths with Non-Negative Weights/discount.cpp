#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const Lli MAX = 1e18;
const I N = 1e5;

vector<pair<I, Lli>> adjs[N];
priority_queue<tuple<Lli, I, B>, vector<tuple<Lli, I, B>>, greater<tuple<Lli, I, B>>> que;
Lli csts[2][N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("discount.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b;
    Lli c;
    cin >> a >> b >> c;
    adjs[a - 1].push_back({b - 1, c});
  }
  for (I i = 0; i < 2; i++)
    fill_n(csts[i], n, MAX);
  que.push({csts[0][0] = 0, 0, true});
  while (!que.empty()) {
    const auto [cst, a, ful] = que.top();
    que.pop();
    if (ful) {
      if (cst == csts[0][a]) {
        for (const auto [b, c] : adjs[a]) {
          if (cst + c < csts[0][b])
            que.push({csts[0][b] = cst + c, b, true});
          if (cst + c / 2 < csts[1][b])
            que.push({csts[1][b] = cst + c / 2, b, false});
        }
      }
    } else
      if (cst == csts[1][a])
        for (const auto [b, c] : adjs[a])
          if (cst + c < csts[1][b])
            que.push({csts[1][b] = cst + c, b, false});
  }
  printf("%lli\n", csts[1][n - 1]);
  return 0;
}