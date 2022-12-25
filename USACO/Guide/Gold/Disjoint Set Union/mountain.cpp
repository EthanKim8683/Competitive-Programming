#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;

const I N = 1e3;
const I M = 1e3;

tuple<I, I, I> vals[N * M];
I h_arr[N * M];
I inds[N * M];
I lows[N * M];
I low_pars[N * M];
I low_rnks[N * M];
I hgh_pars[N * M];
I hgh_rnks[N * M];
I low;
I m;

I cps(I r, I c) {
  return r * m + c;
}

I low_fnd(I i) {
  if (low_pars[i] == -1)
    return i;
  return low_pars[i] = low_fnd(low_pars[i]);
}

I hgh_fnd(I i) {
  if (hgh_pars[i] == -1)
    return i;
  return hgh_pars[i] = hgh_fnd(hgh_pars[i]);
}

void low_uni(I a, I b) {
  a = low_fnd(a);
  b = low_fnd(b);
  if (a == b)
    return;
  if (low_rnks[a] < low_rnks[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  low_pars[b] = a;
  if (low_rnks[a] == low_rnks[b])
    low_rnks[a]++;
}

void cmb(I a, I b) {
  const I t = a;
  a = inds[a];
  b = inds[b];
  if (h_arr[a] == h_arr[b])
    low_uni(a, b);
  else if (h_arr[a] > h_arr[b])
    lows[low_fnd(b)] = low;
  else {
    lows[low_fnd(a)] = low;
    inds[t] = b;
  }
}

void hgh_uni(I a, I b) {
  a = hgh_fnd(a);
  b = hgh_fnd(b);
  if (a == b)
    return;
  if (hgh_rnks[a] < hgh_rnks[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  hgh_pars[b] = a;
  if (hgh_rnks[a] == hgh_rnks[b])
    hgh_rnks[a]++;
  cmb(a, b);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("mountain.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> m;
  fill_n(hgh_pars, n * m, -1);
  fill_n(low_pars, n * m, -1);
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      I h;
      cin >> h;
      h_arr[cps(i, j)] = h;
      inds[cps(i, j)] = cps(i, j);
      vals[cps(i, j)] = {h, i, j};
    }
  }
  sort(vals, vals + n * m, greater<tuple<I, I, I>>());
  for (I i = 0; i < n * m; i++) {
    const auto [h, r, c] = vals[i];
    low = h;
    if (r - 1 >= 0 && h_arr[cps(r - 1, c)] >= h)
      hgh_uni(cps(r, c), cps(r - 1, c));
    if (c - 1 >= 0 && h_arr[cps(r, c - 1)] >= h)
      hgh_uni(cps(r, c), cps(r, c - 1));
    if (r + 1 < n && h_arr[cps(r + 1, c)] >= h)
      hgh_uni(cps(r, c), cps(r + 1, c));
    if (c + 1 < m && h_arr[cps(r, c + 1)] >= h)
      hgh_uni(cps(r, c), cps(r, c + 1));
  }
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++)
      printf("%i ", h_arr[cps(i, j)] - lows[low_fnd(cps(i, j))]);
    printf("\n");
  }
  return 0;
}