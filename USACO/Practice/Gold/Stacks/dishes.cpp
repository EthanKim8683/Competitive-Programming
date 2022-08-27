#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;

I diss[N];
vector<I> bots;
vector<I> stas[N];

I main(void) {
#ifndef ETHANKIM8683
  freopen("dishes.in", "r", stdin);
  freopen("dishes.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> diss[i];
  I cle = 0;
  I len = 0;
  I beg = 0;
  for (; len < n; len++) {
    const I dis = diss[len];
    const auto it = upper_bound(bots.begin(), bots.end(), dis);
    if (it == bots.end()) {
      stas[bots.size()].push_back(dis);
      bots.push_back(dis);
    } else {
      const I ind = it - bots.begin();
      if (ind < beg || dis < cle)
        break;
      if (dis > stas[ind].back()) {
        for (; beg < ind; beg++) {
          while (!stas[beg].empty()) {
            cle = stas[beg].back();
            stas[beg].pop_back();
          }
        }
        while (dis > stas[ind].back()) {
          cle = stas[ind].back();
          stas[ind].pop_back();
        }
      }
      stas[ind].push_back(dis);
    }
  }
  printf("%i\n", len);
  return 0;
}