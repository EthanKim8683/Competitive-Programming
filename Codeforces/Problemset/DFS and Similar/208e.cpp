#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;
const I LOGN = 17;

vector<I> roots;
vector<I> adjs[N];
I ancs[N][LOGN];
I tims[N];
I deps[N];
I cnts[N];
I bnds[N + 1];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I dep = 0;

void dfs(I a, I p) {
  deps[tim] = dep;
  cnts[dep]++;
  tim_begs[a] = tim++;
  ancs[a][0] = p;
  for (I i = 1; i < LOGN; i++)
    ancs[a][i] = ancs[ancs[a][i - 1]][i - 1];
  dep++;
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  dep--;
  tim_ends[a] = tim;
}

B cmp(I a, I b) {
  if (deps[a] == deps[b])
    return a < b;
  return deps[a] < deps[b];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("208e.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I r;
    cin >> r;
    if (r == 0)
      roots.emplace_back(i);
    else
      adjs[r - 1].emplace_back(i);
  }
  for (const auto a : roots)
    dfs(a, a);
  for (I i = 0; i < tim; i++)
    tims[i] = i;
  sort(tims, tims + tim, cmp);
  for (I i = 0; i < N; i++)
    bnds[i + 1] = bnds[i] + cnts[i];
  I m;
  cin >> m;
  while (m--) {
    I v, p;
    cin >> v >> p;
    v--;
    const auto dep = deps[tim_begs[v]];
    I t = p;
    I stp = 1 << LOGN;
    for (I i = LOGN; i--;) {
      stp >>= 1;
      if (stp <= t) {
        t -= stp;
        v = ancs[v][i];
      }
    }
    const auto tim_beg = tim_begs[v];
    const auto tim_end = tim_ends[v];
    I res = 0;
    if (deps[tim_beg] + p == dep) {
      auto l = bnds[dep];
      auto r = bnds[dep + 1] - 1;
      while (l < r) {
        const I m = l + (r - l) / 2;
        if (tims[m] < tim_beg)
          l = m + 1;
        else
          r = m;
      }
      const I a = l;
      l = bnds[dep];
      r = bnds[dep + 1] - 1;
      while (l < r) {
        const I m = l + (r - l + 1) / 2;
        if (tims[m] > tim_end)
          r = m - 1;
        else
          l = m;
      }
      const I b = l;
      res = b - a;
    }
    printf("%i ", res);
  }
  return 0;
}