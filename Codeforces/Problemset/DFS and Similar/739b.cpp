#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

vector<I> adjs[200000];
I a_arr[200000];
I w_arr[200000];
Lli cache_ps[200000];
I cache_node[200000];
I ps[200000];
I result[200000];
I depth = 0;

void dfs1(I v, Lli sum) {
  sum += w_arr[v];
  cache_ps[depth] = sum;
  cache_node[depth] = v;
  // dist(v, u) <= a_arr[u]
  // ps[u] - ps[v] <= a_arr[u]
  // ps[u] - a_arr[u] <= ps[v]
  const Lli value = sum - a_arr[v];
  I l = 0;
  I r = depth;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (value > cache_ps[m])
      l = m + 1;
    else
      r = m;
  }
  if (l < depth) {
    ps[cache_node[l]]--;
    ps[v]++;
  }
  depth++;
  for (const auto u : adjs[v])
    dfs1(u, sum);
  depth--;
}

I dfs2(I v) {
  I sum = 0;
  for (const auto u : adjs[v])
    sum += dfs2(u);
  result[v] = sum;
  sum += ps[v];
  return sum;
}

I main(void) {
#if defined(ETHANKIM8683)
  freopen("739b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 1; i < n; i++) {
    I p;
    cin >> p >> w_arr[i];
    adjs[p - 1].push_back(i);
  }
  dfs1(0, 0);
  dfs2(0);
  for (I i = 0; i < n; i++)
    printf("%i ", result[i]);
  return 0;
}