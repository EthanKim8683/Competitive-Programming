#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;
const I LOGN = 18;;

vector<I> adjs[N];
I ancs[N][LOGN];
I deps[N];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I dep = 0;

void dfs(I a, I p) {
  tim_begs[a] = tim++;
  deps[a] = dep++;
  ancs[a][0] = p;
  for (I i = 1; i < LOGN; i++)
    ancs[a][i] = ancs[ancs[a][i - 1]][i - 1];
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  dep--;
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
  freopen("distance.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0, 0);
  while (q--) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    const auto c = lca(a, b);
    printf("%i\n", deps[a] + deps[b] - 2 * deps[c]);
  }
  return 0;
}