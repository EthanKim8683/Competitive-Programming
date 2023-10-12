#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 2500;

vector<I> adjs[N];
queue<I> stts;
I deps[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("girth.in", "r", stdin);
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
  I res = 1e9;
  for (I i = n; i--;) {
    fill_n(deps, n, -1);
    deps[i] = 0;
    stts.push(i);
    while (!stts.empty()) {
      const auto a = stts.front();
      stts.pop();
      for (const auto b : adjs[a]) {
        if (deps[b] == -1) {
          deps[b] = deps[a] + 1;
          stts.push(b);
        } else if (deps[b] >= deps[a])
          res = min(res, 1 + deps[a] + deps[b]);
      }
    }
  }
  if (res == 1e9)
    printf("-1\n");
  else
    printf("%i\n", res);
  return 0;
}