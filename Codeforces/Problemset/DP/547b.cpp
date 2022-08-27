#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;

I a_arr[N];
I pars[N];
I inds[N];
B viss[N];
I sizs[N + 1];

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

I siz(I x) {
  return -pars[fnd(x)];
}

void uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
}

B cmp(I a, I b) {
  return a_arr[a] > a_arr[b];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  iota(inds, inds + n, 0);
  sort(inds, inds + n, cmp);
  for (I i = 0; i < n; i++) {
    const I a = inds[i];
    viss[a] = true;
    if (a - 1 >= 0 && viss[a - 1])
      uni(a, a - 1);
    if (a + 1 < n && viss[a + 1])
      uni(a, a + 1);
    const I ind = siz(a);
    sizs[ind] = max(sizs[ind], a_arr[a]);
  }
  for (I i = n; i > 1; i--)
    sizs[i - 1] = max(sizs[i - 1], sizs[i]);
  for (I i = 1; i <= n; i++)
    printf("%i ", sizs[i]);
  return 0;
}