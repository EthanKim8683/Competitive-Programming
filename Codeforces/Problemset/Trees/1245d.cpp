#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 2000;

pair<I, I> cits[N];
I c_arr[N];
I k_arr[N];
vector<tuple<Lli, I, I>> edgs;
I pars[N + 1];
vector<I> stns;
vector<pair<I, I>> cons;

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

B uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return false;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  return true;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n + 1, -1);
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    cits[i] = {x, y};
  }
  for (I i = 0; i < n; i++)
    cin >> c_arr[i];
  for (I i = 0; i < n; i++)
    cin >> k_arr[i];
  for (I i = 0; i < n; i++) {
    for (I j = i + 1; j < n; j++) {
      const auto [ix, iy] = cits[i];
      const auto [jx, jy] = cits[j];
      const Lli rte = k_arr[i] + k_arr[j];
      const Lli dis = abs(ix - jx) + abs(iy - jy);
      edgs.push_back({rte * dis, i, j});
    }
  }
  for (I i = 0; i < n; i++)
    edgs.push_back({c_arr[i], i, n});
  sort(edgs.begin(), edgs.end());
  Lli yen = 0;
  for (const auto [cst, i, j] : edgs) {
    if (uni(i, j)) {
      yen += cst;
      if (j == n)
        stns.push_back(i);
      else
        cons.push_back({i, j});
    }
  }
  printf("%lli\n", yen);
  printf("%i\n", stns.size());
  for (const auto stn : stns)
    printf("%i ", stn + 1);
  printf("\n");
  printf("%i\n", cons.size());
  for (const auto [i, j] : cons)
    printf("%i %i\n", i + 1, j + 1);
  return 0;
}