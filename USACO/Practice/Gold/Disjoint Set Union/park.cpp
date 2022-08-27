#include <iostream>
#include <cstdio>
#include <tuple>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using S = string;
using B = bool;

/*
it's all about the walls:

4    B    3
  |`````|
A |     | C
  |_____|
1    D    2

A <-> B separates 4 from 3, 2 and 1
A <-> C separates 4 and 3 from 2 and 1
C <-> D separates 2 from 4, 3 and 1
etc.

We can union nodes by size, increasing,
to block fatter visitors from passing
*/

const I N = 2000;
const I M = 1e5;

tuple<I, I, I> tres[N];
pair<I, I> viss[M];
vector<tuple<I, I, I>> edgs;
vector<tuple<I, I, I>> stks;
I pars[N + 4];
B cuts[4][4];
S ress[M];

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

void uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
}

B con(I a, I b) {
  return fnd(a) == fnd(b);
}

I dis(I x1, I y1, I x2, I y2) {
  const Lli x = x1 - x2;
  const Lli y = y1 - y2;
  return (I) sqrt(x * x + y * y);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  I w, h;
  cin >> w >> h;
  for (I i = 0; i < n; i++)
    cin >> get<0>(tres[i]) >> get<1>(tres[i]) >> get<2>(tres[i]);
  for (I i = 0; i < m; i++)
    cin >> get<0>(viss[i]) >> get<1>(viss[i]);
  for (I i = 0; i < m; i++)
    stks.push_back({viss[i].first * 2, viss[i].second - 1, i});
  fill_n(pars, n + 4, -1);
  edgs.push_back({w, n + 0, n + 2});
  edgs.push_back({h, n + 1, n + 3});
  for (I i = 0; i < n; i++) {
    const auto [x, y, r] = tres[i];
    edgs.push_back({x - r, i, n + 0});
    edgs.push_back({y - r, i, n + 1});
    edgs.push_back({w - x - r, i, n + 2});
    edgs.push_back({h - y - r, i, n + 3});
  }
  for (I i = 0; i < n; i++) {
    for (I j = i + 1; j < n; j++) {
      const auto [x1, y1, r1] = tres[i];
      const auto [x2, y2, r2] = tres[j];
      edgs.push_back({dis(x1, y1, x2, y2) - r1 - r2, i, j});
    }
  }
  sort(edgs.begin(), edgs.end());
  sort(stks.begin(), stks.end(), greater<tuple<I, I, I>>());
  for (const auto [len, i, j] : edgs) {
    while (!stks.empty() && get<0>(stks.back()) <= len) {
      const auto [r, e, i] = stks.back();
      stks.pop_back();
      for (I j = 0; j < 4; j++)
        if (!cuts[min(e, j)][max(e, j)])
          ress[i] += to_string(j + 1);
    }
    uni(i, j);
    if (con(n + 0, n + 1))
      cuts[0][1] = cuts[0][2] = cuts[0][3] = true;
    if (con(n + 0, n + 2))
      cuts[0][2] = cuts[0][3] = cuts[1][2] = cuts[1][3] = true;
    if (con(n + 0, n + 3))
      cuts[0][3] = cuts[1][3] = cuts[2][3] = true;
    if (con(n + 1, n + 2))
      cuts[0][1] = cuts[1][2] = cuts[1][3] = true;
    if (con(n + 1, n + 3))
      cuts[0][1] = cuts[0][2] = cuts[1][3] = cuts[2][3] = true;
    if (con(n + 2, n + 3))
      cuts[0][2] = cuts[1][2] = cuts[2][3] = true;
  }
  for (I i = 0; i < m; i++)
    printf("%s\n", ress[i].c_str());
  return 0;
}