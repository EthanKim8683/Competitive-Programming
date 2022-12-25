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
I tim_begs[N];
I tim_ends[N];
I tim = 0;

void dfs(I a, I p) {
  tim_begs[a] = tim++;
  ancs[a][0] = p;
  for (I i = 1; i < LOGN; i++)
    ancs[a][i] = ancs[ancs[a][i - 1]][i - 1];
  for (const auto b : adjs[a])
    dfs(b, a);
  tim_ends[a] = tim++;
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
  for (I i = LOGN; i--;)
    if (!is_anc(ancs[a][i], b))
      a = ancs[a][i];
  return ancs[a][0];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("company2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 1; i < n; i++) {
    I e;
    cin >> e;
    adjs[e - 1].push_back(i);
  }
  dfs(0, 0);
  while (q--) {
    I a, b;
    cin >> a >> b;
    printf("%i\n", lca(a - 1, b - 1) + 1);
  }
  return 0;
}