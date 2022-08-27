#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const I MAX = 1e9;

pair<I, I> adjs[N];
vector<I> cycs;
I viss[N];
Lli res = 0;

I dfs(I a) {
  if (viss[a] == 1)
    return a;
  if (viss[a] == 2)
    return -1;
  viss[a] = 1;
  const auto [b, v] = adjs[a];
  res += v;
  const I cyc = dfs(b);
  if (cyc != -1)
    cycs.push_back(v);
  viss[a] = 2;
  if (cyc == a)
    return -1;
  return cyc;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, v;
    cin >> a >> v;
    adjs[i] = {a - 1, v};
  }
  for (I i = 0; i < n; i++) {
    cycs.clear();
    dfs(i);
    if (!cycs.empty()) {
      I cut = MAX;
      for (const auto v : cycs)
        cut = min(cut, v);
      res -= cut;
    }
  }
  printf("%lli\n", res);
  return 0;
}