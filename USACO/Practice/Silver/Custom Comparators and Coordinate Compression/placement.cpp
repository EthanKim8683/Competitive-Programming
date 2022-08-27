#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

map<I, vector<pair<I, I>>> wids;
multimap<I, I, greater<I>> pres;
I ress[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    wids.clear();
    pres.clear();
    for (I i = 0; i < n; i++) {
      I w, h;
      cin >> w >> h;
      wids[w].push_back({h, i});
      wids[h].push_back({w, i});
    }
    fill_n(ress, n, -1);
    for (const auto& [wid, heis] : wids) {
      for (const auto [hei, i] : heis) {
        auto it = pres.upper_bound(hei);
        if (it != pres.end()) {
          if (it->second == i)
            it++;
          if (it != pres.end())
            ress[i] = it->second + 1;
        }
      }
      for (const auto [hei, i] : heis)
        pres.insert({hei, i});
    }
    for (I i = 0; i < n; i++)
      printf("%i ", ress[i]);
    printf("\n");
  }
  return 0;
}