#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 100000;

vector<I> adjs[N];
I p_arr[N];
I inds[N];
I segs[2 * N];
I ress[N];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I n;

B cmp(I a, I b) {
  return p_arr[a] > p_arr[b];
}

void upd(I i, I val) {
  for (segs[i += n] = val; i > 1; i >>= 1)
    segs[i >> 1] = segs[i] + segs[i ^ 1];
}

I qry(I l, I r) {
  I res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res += segs[l++];
    if (r & 1)
      res += segs[--r];
  }
  return res;
}

void dfs(I a, I p = -1) {
  tim_begs[a] = tim++;
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  tim_ends[a] = tim;
}

I main(void) {
  freopen("promote.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("promote.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  for (I i = 1; i < n; i++) {
    I j;
    cin >> j;
    adjs[j - 1].push_back(i);
  }
  dfs(0);
  for (I i = 0; i < n; i++)
    inds[i] = i;
  sort(inds, inds + n, cmp);
  for (I i = 0; i < n; i++) {
    const auto a = inds[i];
    ress[a] = qry(tim_begs[a], tim_ends[a]);
    upd(tim_begs[a], 1);
  }
  for (I i = 0; i < n; i++)
    printf("%i\n", ress[i]);
  return 0;
}