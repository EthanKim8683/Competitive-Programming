#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

vector<I> adjs[N];
vector<I> deps[N];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I dep = 0;

void dfs(I a) {
  tim_begs[a] = tim;
  deps[dep++].push_back(tim++);
  for (const auto b : adjs[a])
    dfs(b);
  dep--;
  tim_ends[a] = tim;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("count.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 1; i < n; i++) {
    I p;
    cin >> p;
    adjs[p - 1].push_back(i);
  }
  dfs(0);
  I q;
  cin >> q;
  for (I i = 0; i < q; i++) {
    I u, d;
    cin >> u >> d;
    u--;
    const auto beg_it = deps[d].begin();
    const auto end_it = deps[d].end();
    const auto beg = lower_bound(beg_it, end_it, tim_begs[u]);
    const auto end = lower_bound(beg_it, end_it, tim_ends[u]);
    printf("%i\n", end - beg);
  }
  return 0;
}