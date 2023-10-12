#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;

vector<I> adjs[200000];
queue<I> states;
I dists[200000];
I parents[200000];
I result[200000];

I main(void) {
#ifdef ETHANKIM8683
  freopen("route.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  while (m--) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  fill_n(dists, n, 1e9);
  dists[0] = 0;
  states.push(0);
  while (!states.empty()) {
    const I a = states.front();
    states.pop();
    const I dist = dists[a] + 1;
    for (const auto b : adjs[a]) {
      if (dists[b] == 1e9) {
        dists[b] = dist;
        parents[b] = a;
        states.push(b);
      }
    }
  }
  I x = n - 1;
  I dist = dists[x];
  if (dist == 1e9)
    printf("IMPOSSIBLE");
  else {
    dist++;
    printf("%i\n", dist);
    for (I i = dist; i--;) {
      result[i] = x;
      x = parents[x];
    }
    for (I i = 0; i < dist; i++)
      printf("%i ", result[i] + 1);
  }
  return 0;
}