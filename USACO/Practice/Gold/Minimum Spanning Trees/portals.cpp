#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 1e5;

vector<I> pors[2 * N];
I pars[2 * N];
tuple<I, I, I> edgs[N];

I fnd(I i) {
  if (pars[i] < 0)
    return i;
  return pars[i] = fnd(pars[i]);
}

B uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return false;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  return true;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("portals.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, 2 * n, -1);
  for (I i = 0; i < n; i++) {
    I c, p1, p2, p3, p4;
    cin >> c >> p1 >> p2 >> p3 >> p4;
    const I j = i * 2;
    const I k = j + 1;
    pors[p1 - 1].push_back(j);
    pors[p2 - 1].push_back(j);
    pors[p3 - 1].push_back(k);
    pors[p4 - 1].push_back(k);
    edgs[i] = {c, j, k};
  }
  for (I i = 0; i < 2 * n; i++)
    uni(pors[i][0], pors[i][1]);
  sort(edgs, edgs + n);
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const auto [c, j, k] = edgs[i];
    if (uni(j, k))
      res += c;
  }
  printf("%lli\n", res);
  return 0;
}