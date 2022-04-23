#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define N 200000

using namespace std;

using I = int;
using B = bool;

vector<I> adjs[N];
I special[N];
I queue[N];
I a_dists[N];
I b_dists[N];
pair<I, I> cache[N];
I n;

void bfs(I* dists, I root) {
  fill_n(dists, n, 1e9);
  I queue_beg = 0;
  I queue_end = 1;
  dists[root] = 0;
  queue[0] = root;
  while (queue_beg < queue_end) {
    const I x = queue[queue_beg];
    queue_beg++;
    const I dist = dists[x] + 1;
    for (const auto y : adjs[x]) {
      if (dists[y] == 1e9) {
        dists[y] = dist;
        queue[queue_end] = y;
        queue_end++;
      }
    }
  }
}

B cmp(I a, I b) {
  return b_dists[a] < b_dists[b];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1307d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I m, k;
  cin >> n >> m >> k;
  const I p = n - 1;
  for (I i = k; i--;) {
    I a;
    cin >> a;
    special[i] = a - 1;
  }
  for (I i = m; i--;) {
    I x, y;
    cin >> x >> y;
    x--;
    y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  bfs(a_dists, 0);
  bfs(b_dists, p);
  for (I i = k; i--;) {
    const I a = special[i];
    cache[i] = {a_dists[a] - b_dists[a], a};
  }
  sort(cache, cache + k);
  I result = 0;
  I prefix = -1e9;
  for (I i = 0; i < k; i++) {
    const I a = cache[i].second;
    result = max(result, b_dists[a] + prefix);
    prefix = max(prefix, a_dists[a]);
  }
  printf("%i\n", min(result + 1, a_dists[p]));
  return 0;
}