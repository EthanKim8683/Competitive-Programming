#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 1e5;
const I LOGN = 17;

vector<I> adjs[N];
I e_arr[N];
I segs[N * 2];
I a_tim_begs[N];
I a_tim_ends[N];
I b_tim_begs[N];
I b_tim_ends[N];
pair<I, I> sprs[8 * N][3 + LOGN];
I a_tim = 0;
I b_tim = 0;
I dep = 0;
I n;

void upd(I l, I r, Lli val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      segs[l++] ^= val;
    if (r & 1)
      segs[--r] ^= val;
  }
}

I qry(I i) {
  Lli res = 0;
  for (i += n; i > 0; i >>= 1)
    res ^= segs[i];
  return res;
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
  upd(a_tim_begs[a], a_tim_ends[a], e_arr[a]);
}

I main(void) {
  freopen("cowland.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("cowland.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> e_arr[i];
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  bld();
  while (q--) {
    I t;
    cin >> t;
    if (t == 1) {
      I i, v;
      cin >> i >> v;
      i--;
      upd(a_tim_begs[i], a_tim_ends[i], v ^ e_arr[i]);
      e_arr[i] = v;
    } else if (t == 2) {
      I i, j;
      cin >> i >> j;
      i--;
      j--;
      const I k = lca(i, j);
      printf("%lli\n", qry(a_tim_begs[i]) ^ qry(a_tim_begs[j]) ^ e_arr[k]);
    }
  }
  return 0;
}