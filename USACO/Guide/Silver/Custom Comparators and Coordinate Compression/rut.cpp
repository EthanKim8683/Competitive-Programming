#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 1000;

pair<I, I> cows[N];
vector<I> e_inds;
vector<I> n_inds;
map<I, vector<tuple<B, I, I>>> movs;
B hits[N][N];
B stps[N];
B viss[N];
vector<I> adjs[N];
vector<I> tmps;
I blms[N];

I dfs(I a) {
  if (!viss[a]) {
    viss[a] = true;
    for (const auto b : adjs[a])
      blms[a] += dfs(b);
  }
  return blms[a] + 1;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    C chr;
    I x, y;
    cin >> chr >> x >> y;
    cows[i] = {x, y};
    if (chr == 'E')
      e_inds.push_back(i);
    if (chr == 'N')
      n_inds.push_back(i);
  }
  for (const auto e : e_inds) {
    for (const auto n : n_inds) {
      const auto [e_x, e_y] = cows[e];
      const auto [n_x, n_y] = cows[n];
      const I e_dis = n_x - e_x;
      const I n_dis = e_y - n_y;
      if (e_dis >= 0 && n_dis >= 0) {
        if (e_dis < n_dis) {
          movs[e_dis].push_back({true, e, n});
          movs[n_dis].push_back({false, e, n});
        } else if (n_dis < e_dis) {
          movs[n_dis].push_back({true, n, e});
          movs[e_dis].push_back({false, n, e});
        }
      }
    }
  }
  for (const auto [dis, ints] : movs) {
    for (const auto [hit, a, b] : ints) {
      if (hit) {
        if (!stps[a] && !stps[b])
          hits[a][b] = true;
      } else {
        if (hits[a][b] && !stps[b]) {
          adjs[a].push_back(b);
          tmps.push_back(b);
        }
      }
    }
    for (const auto tmp : tmps)
      stps[tmp] = true;
    tmps.clear();
  }
  for (I i = 0; i < n; i++)
    dfs(i);
  for (I i = 0; i < n; i++)
    printf("%i\n", blms[i]);
  return 0;
}