#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;
const I LOGN = 18;

vector<I> adjs[N];
I ancs[N][LOGN];
I cnts[N];
I deps[N];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I dep = 0;

I dfs(I a, I p) {
  tim_begs[a] = tim++;
  deps[a] = dep;
  ancs[a][0] = p;
  for (int i = 1; i < LOGN; i++)
    ancs[a][i] = ancs[ancs[a][i - 1]][i - 1];
  dep++;
  I cnt = 1;
  for (const auto b : adjs[a])
    if (b != p)
      cnt += dfs(b, a);
  cnts[a] = cnt;
  dep--;
  tim_ends[a] = tim++;
  return cnt;
}

B is_anc(I a, I b) {
  return tim_begs[a] <= tim_begs[b] && 
         tim_ends[a] >= tim_ends[b];
}

I lca(I a, I b) {
  if (is_anc(a, b))
    return a;
  if (is_anc(b, a))
    return b;
  for (int i = LOGN; i--;)
    if (!is_anc(ancs[a][i], b))
      a = ancs[a][i];
  return ancs[a][0];
}

I cnt(I a, I b) {
  if (is_anc(b, a)) {
    for (int i = LOGN; i--;)
      if (!is_anc(ancs[a][i], b))
        a = ancs[a][i];
    return cnts[a];
  } else
    return cnts[0] - cnts[b];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("519e.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = n; --i;) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].emplace_back(b);
    adjs[b].emplace_back(a);
  }
  dfs(0, 0);
  I m;
  cin >> m;
  while (m--) {
    I x, y;
    cin >> x >> y;
    I res = 0;
    if (x != y) {
      x--;
      y--;
      const I z = lca(x, y);
      const I x_dis = deps[x] - deps[z];
      const I y_dis = deps[y] - deps[z];
      const I dia = x_dis + y_dis;
      if (dia % 2 == 0) {
        I rad = dia / 2;
        I stp = 1 << LOGN;
        I mid = x_dis > y_dis ? x : y;
        for (I i = LOGN; i--;) {
          stp >>= 1;
          if (stp <= rad) {
            rad -= stp;
            mid = ancs[mid][i];
          }
        }
        res = n - cnt(x, mid) - cnt(y, mid);
      }
    } else
      res = n;
    printf("%i\n", res);
  }
  return 0;
}