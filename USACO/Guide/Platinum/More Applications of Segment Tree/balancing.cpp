#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <map>

// querying for `a` for all possible values of `b`
// yields O(nlog(n))... not bad?

using namespace std;

using I = int;
using B = bool;

const I N = 100000;
const I LOGN = 17;
const I FIXN = 1 << LOGN;
const I MAX = 1e9;

unordered_map<I, I> x_cpss;
I x_crds[N];
map<I, unordered_map<I, I>> y_crds;
I bot_segs[2 * FIXN];
I top_segs[2 * FIXN];

I cps(I i) {
  auto it = x_cpss.find(i);
  if (it == x_cpss.end())
    it = x_cpss.insert({i, x_cpss.size()}).first;
  return it->second;
}

void add(I segs[], I i, I val) {
  segs[i + FIXN] += val;
}

void bld(I segs[]) {
  for (I i = FIXN - 1; i > 0; i--)
    segs[i] = segs[i << 1] + segs[i << 1 | 1];
}

void upd(I segs[], I i, I val) {
  for (segs[i += FIXN] += val; i > 1; i >>= 1)
    segs[i >> 1] = segs[i] + segs[i ^ 1];
}

I qry() {
  I bot_lft_tot = 0;
  I top_lft_tot = 0;
  I bot_rgt_tot = 0;
  I top_rgt_tot = 0;
  I cur_ind = 1;
  I res = MAX;
  for (I i = 0; i < LOGN; i++) {
    const I lft_ind = cur_ind << 1;
    const I rgt_ind = lft_ind | 1;
    const I bot_lft_cnt = bot_lft_tot + bot_segs[lft_ind];
    const I top_lft_cnt = top_lft_tot + top_segs[lft_ind];
    const I bot_rgt_cnt = bot_rgt_tot + bot_segs[rgt_ind];
    const I top_rgt_cnt = top_rgt_tot + top_segs[rgt_ind];
    const I lft_max = max(bot_lft_cnt, top_lft_cnt);
    const I rgt_max = max(bot_rgt_cnt, top_rgt_cnt);
    res = min(res, max(lft_max, rgt_max));
    if (lft_max == rgt_max)
      break;
    if (lft_max > rgt_max) {
      bot_rgt_tot = bot_rgt_cnt;
      top_rgt_tot = top_rgt_cnt;
      cur_ind = lft_ind;
    } else {
      bot_lft_tot = bot_lft_cnt;
      top_lft_tot = top_lft_cnt;
      cur_ind = rgt_ind;
    }
  }
  return res;
}

I main(void) {
  freopen("balancing.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("balancing.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, y;
    cin >> x >> y;
    x_crds[i] = x;
    y_crds[y][x]++;
  }
  sort(x_crds, x_crds + n);
  for (I i = 0; i < n; i++)
    add(bot_segs, cps(x_crds[i]), 1);
  bld(bot_segs);
  I res = qry();
  for (const auto& [y_crd, crds] : y_crds) {
    for (const auto [x_crd, cnt] : crds) {
      const auto x_cps = cps(x_crd);
      upd(bot_segs, x_cps, -cnt);
      upd(top_segs, x_cps, cnt);
    }
    res = min(res, qry());
  }
  printf("%i\n", res);
  return 0;
}