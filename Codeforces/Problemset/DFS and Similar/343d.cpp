#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

using I = int;
using B = bool;

const I N = 500000;

vector<I> adjs[N];
I tim_begs[N];
I tim_ends[N];
B segs[N];
I pars[N];
I tim = 0;

void dfs(I a, I p = -1) {
  tim_begs[a] = tim++;
  pars[a] = p;
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  tim_ends[a] = tim;
}

void fill(I a) {
  B emp = false;
  for (I i = tim_begs[a]; i < tim_ends[a]; i++) {
    if (!segs[i]) {
      emp = true;
      segs[i] = true;
    }
  }
  if (emp && pars[a] != -1)
    segs[tim_begs[pars[a]]] = false;
}

void empty(I a) {
  segs[tim_begs[a]] = false;
}

B check(I a) {
  for (I i = tim_begs[a]; i < tim_ends[a]; i++)
    if (!segs[i])
      return false;
  return true;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("343d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = n; --i;) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  I q;
  cin >> q;
  while (q--) {
    I c, v;
    cin >> c >> v;
    v--;
    if (c == 1)
      fill(v);
    else if (c == 2)
      empty(v);
    else if (c == 3)
      printf("%i\n", check(v));
  }
  return 0;
}