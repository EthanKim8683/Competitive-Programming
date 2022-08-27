#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;

pair<I, I> cows[2][N];
multimap<I, I> unvs[2];
queue<tuple<I, I, I>> que;
I deps[2][N];

void add(I val, I cow, I ind, I dep) {
  deps[cow][ind] = dep;
  que.push({val, cow, dep});
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("piepie.in", "r", stdin);
  freopen("piepie.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fill(&deps[0][0], &deps[0][0] + sizeof(deps) / sizeof(I), -1);
  I n, d;
  cin >> n >> d;
  for (I i = 0; i < n; i++)
    cin >> cows[0][i].first >> cows[0][i].second;
  for (I i = 0; i < n; i++)
    cin >> cows[1][i].second >> cows[1][i].first;
  for (I i = 0; i < 2; i++) {
    for (I j = 0; j < n; j++) {
      const auto [thi, tha] = cows[i][j];
      if (tha == 0)
        add(thi, i, j, 1);
      else
        unvs[i].insert({tha, j});
    }
  }
  while (!que.empty()) {
    const auto [val, cow, dep] = que.front();
    que.pop();
    const auto beg = unvs[!cow].lower_bound(val - d);
    const auto end = unvs[!cow].upper_bound(val);
    for (auto it = beg; it != end; it = unvs[!cow].erase(it)) {
      const auto ind = it->second;
      const auto [thi, tha] = cows[!cow][ind];
      add(thi, !cow, ind, dep + 1);
    }
  }
  for (I i = 0; i < n; i++)
    printf("%i\n", deps[0][i]);
  return 0;
}