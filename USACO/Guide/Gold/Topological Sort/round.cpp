#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<I> adjs[N];
I viss[N];
I pars[N];
I cyc_beg, cyc_end;
vector<I> ress;

B dfs(I a) {
  viss[a] = 1;
  for (const auto b : adjs[a]) {
    if (!viss[b]) {
      pars[b] = a;
      if (dfs(b))
        return true;
    } else if (viss[b] == 1) {
      cyc_beg = b;
      cyc_end = a;
      return true;
    }
  }
  viss[a] = 2;
  return false;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("round.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  for (I i = 0; i < n; i++) {
    if (!viss[i] && dfs(i)) {
      ress.push_back(cyc_beg);
      for (I j = cyc_end; j != cyc_beg; j = pars[j])
        ress.push_back(j);
      ress.push_back(cyc_beg);
      reverse(ress.begin(), ress.end());
      printf("%i\n", ress.size());
      for (const auto res : ress)
        printf("%i ", res + 1);
      return 0;
    }
  }
  printf("IMPOSSIBLE\n");
  return 0;
}