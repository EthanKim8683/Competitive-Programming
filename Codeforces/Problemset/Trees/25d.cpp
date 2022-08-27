#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 1000;

pair<I, I> edgs[N - 1];
I pars[N];
vector<I> rems;
vector<I> coms;

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
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
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    edgs[i] = {a - 1, b - 1};
  }
  for (I i = 0; i < n - 1; i++) {
    const auto [a, b] = edgs[i];
    if (!uni(a, b))
      rems.push_back(i);
  }
  for (I i = 0; i < n; i++)
    if (pars[i] < 0)
      coms.push_back(i);
  printf("%i\n", rems.size());
  for (I i = 0; i < rems.size(); i++) {
    const auto [a, b] = edgs[rems[i]];
    printf("%i %i %i %i\n", a + 1, b + 1, coms[i] + 1, coms[i + 1] + 1);
  }
  return 0;
}