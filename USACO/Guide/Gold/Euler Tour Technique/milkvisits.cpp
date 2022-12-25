#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;
const I M = 1e5;
const I LOGN = 17;

I t_arr[N];
vector<I> adjs[N];
vector<I> cows[N + 1];
vector<tuple<I, I, I>> frds[N + 1];
pair<I, I> segs[N * 2];
pair<I, I> sprs[8 * N][3 + LOGN];
I a_tim_begs[N];
I a_tim_ends[N];
I b_tim_begs[N];
I b_tim_ends[N];
B ress[M];
I a_tim = 0;
I b_tim = 0;
I dep = 0;
I n;

void upd(I l, I r, I val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      if (segs[l].first == val)
        segs[l].second++;
      else
        segs[l] = {val, 1};
      l++;
    }
    if (r & 1) {
      r--;
      if (segs[r].first == val)
        segs[r].second++;
      else
        segs[r] = {val, 1};
    }
  }
}

I qry(I i, I val) {
  I cnt = 0;
  for (i += n; i > 0; i >>= 1)
    if (segs[i].first == val)
      cnt += segs[i].second;
  return cnt;
}

void bld() {
  for (I i = 1; 1 << i <= b_tim; i++)
    for (I j = 0; j + (1 << (i - 1)) < b_tim; j++)
      sprs[j][i] = min(sprs[j][i - 1], sprs[j + (1 << (i - 1))][i - 1]);
}

I lca(I a, I b) {
  const I beg = min(b_tim_begs[a], b_tim_begs[b]);
  const I end = max(b_tim_ends[a], b_tim_ends[b]);
  const I dis = 31 - __builtin_clz(end - beg);
  return min(sprs[beg][dis], sprs[end - (1 << dis)][dis]).second;
}

void dfs(I a, I p = -1) {
  a_tim_begs[a] = a_tim++;
  b_tim_begs[a] = b_tim;
  sprs[b_tim++][0] = {dep++, a};
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      sprs[b_tim++][0] = {dep - 1, a};
    }
  }
  dep--;
  a_tim_ends[a] = a_tim;
  b_tim_ends[a] = b_tim;
}

I main(void) {
  freopen("milkvisits.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("milkvisits.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> n >> m;
  for (I i = 0; i < n; i++) {
    I t;
    cin >> t;
    cows[t].push_back(i);
    t_arr[i] = t;
  }
  for (I i = 0; i < n - 1; i++) {
    I x, y;
    cin >> x >> y;
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    frds[c].push_back({a - 1, b - 1, i});
  }
  dfs(0);
  bld();
  for (I i = 1; i <= n; i++) {
    for (const auto j : cows[i])
      upd(a_tim_begs[j], a_tim_ends[j], i);
    for (const auto [a, b, j] : frds[i]) {
      const I c = lca(a, b);
      ress[j] = qry(a_tim_begs[a], i) + qry(a_tim_begs[b], i) - 2 * qry(a_tim_begs[c], i) + (t_arr[c] == i);
    }
  }
  for (I i = 0; i < m; i++)
    printf("%i", ress[i]);
  return 0;
}