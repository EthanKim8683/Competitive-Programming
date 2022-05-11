#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;
const I SEG = 4e5;

vector<I> adjs[N];
I segs[2 * SEG];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I dep = 0;

void set(I i, I val) {
  segs[i + SEG] = val;
}

void bld() {
  for (I i = SEG - 1; i > 0; i--)
    segs[i] = min(segs[i << 1], segs[i << 1 | 1]);
}

I rng(I l, I r) {
  I res = 1e9;
  for (l += SEG, r += SEG; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res = min(res, segs[l++]);
    if (r & 1)
      res = min(res, segs[--r]);
  }
  return res;
}

I pnt(I i) {
  return segs[i + SEG];
}

void dfs(I a, I p = -1) {
  tim_begs[a] = tim;
  set(tim++, dep++);
  for (const auto b : adjs[a]) {
    if (b != p) {
      dfs(b, a);
      set(tim++, dep - 1);
    }
  }
  dep--;
  tim_ends[a] = tim;
}

B is_anc(I a, I b) {
  return tim_begs[a] <= tim_begs[b] &&
         tim_ends[a] >= tim_ends[b];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("distance2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  fill_n(segs, 4 * n, 1e9);
  dfs(0);
  bld();
  while (q--) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    const auto a_beg = tim_begs[a];
    const auto b_beg = tim_begs[b];
    const auto a_dep = pnt(a_beg);
    const auto b_dep = pnt(b_beg);
    if (is_anc(a, b))
      printf("%i\n", b_dep - a_dep);
    else if (is_anc(b, a))
      printf("%i\n", a_dep - b_dep);
    else {
      const I l = min(a_beg, b_beg);
      const I r = max(a_beg, b_beg);
      printf("%i\n", a_dep + b_dep - 2 * rng(l, r));
    }
  }
  return 0;
}