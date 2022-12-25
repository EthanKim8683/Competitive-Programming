#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const Lli MAX = 1e18;
const I N = 2000;
const I M = 10 * N;
const I LOGM = 15;

vector<pair<I, Lli>> adjs[N];
Lli d_arr[N][N];
tuple<Lli, I, I> edgs[N * N];
I pars[N];
I rnks[N];
Lli sprs[M][LOGM];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I n;

I cps(I r, I c) {
  return r * n + c;
}

I fnd(I i) {
  if (pars[i] == -1)
    return i;
  return pars[i] = fnd(pars[i]);
}

B uni(I a, I b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b)
    return false;
  if (rnks[a] < rnks[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  pars[b] = a;
  if (rnks[a] == rnks[b])
    rnks[a]++;
  return true;
}

void dfs(I a, I p = -1, Lli dep = 0) {
  tim_begs[a] = tim;
  sprs[tim++][0] = dep;
  for (const auto [b, d] : adjs[a]) {
    if (b != p) {
      dfs(b, a, dep + d);
      sprs[tim++][0] = dep;
    }
  }
  tim_ends[a] = tim;
}

void bld() {
  for (I i = 1; 1 << i <= tim; i++)
    for (I j = 0; j + (1 << (i - 1)) < tim; j++)
      sprs[j][i] = min(sprs[j][i - 1], sprs[j + (1 << (i - 1))][i - 1]);
}

Lli pnt(I i) {
  return sprs[i][0];
}

Lli rng(I l, I r) {
  const I dis = 31 - __builtin_clz(r - l);
  return min(sprs[l][dis], sprs[r - (1 << dis)][dis]);
}

Lli dst(I l, I r) {
  const I beg = min(tim_begs[l], tim_begs[r]);
  const I end = max(tim_ends[l], tim_ends[r]);
  return pnt(tim_begs[l]) + pnt(tim_begs[r]) - 2 * rng(beg, end);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("inverse.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  fill_n(pars, N, -1);
  for (I i = 0; i < M; i++)
    fill_n(sprs[i], LOGM, MAX);
  I len = 0;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      Lli d;
      cin >> d;
      d_arr[i][j] = d;
      if (i != j) {
        if (d == 0) {
          printf("NO\n");
          return 0;
        }
        edgs[len++] = {d, i, j};
      }
    }
  }
  sort(edgs, edgs + len);
  for (I i = 0; i < len; i++) {
    const auto [d, a, b] = edgs[i];
    if (uni(a, b)) {
      adjs[a].push_back({b, d});
      adjs[b].push_back({a, d});
    }
  }
  dfs(0);
  bld();
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      if (dst(i, j) != d_arr[i][j]) {
        printf("NO\n");
        return 0;
      }
    }
  }
  printf("YES\n");
  return 0;
}