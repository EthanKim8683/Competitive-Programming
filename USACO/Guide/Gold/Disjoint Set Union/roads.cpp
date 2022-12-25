#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I N = 2e5;

I reps[N];
I rnks[N];
pair<I, I> pars[N];
vector<pair<I, I>> ancs[N];
I day = 1;

I fnd(I i) {
  if (reps[i] == -1)
    return i;
  return reps[i] = fnd(reps[i]);
}

void bld(I i) {
  pair<I, I> anc = {i, 0};
  do {
    ancs[i].push_back(anc);
    anc = pars[anc.first];
  } while (anc.second != -1);
}

void uni(I a, I b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b)
    return;
  if (rnks[a] < rnks[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  reps[b] = a;
  pars[b] = {a, day};
  if (rnks[a] == rnks[b])
    rnks[a]++;
}

I qry(I a, I b) {
  for (const auto a_anc : ancs[a])
    for (const auto b_anc : ancs[b])
      if (a_anc.first == b_anc.first)
        return max(a_anc.second, b_anc.second);
  return -1;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("roads.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, q;
  cin >> n >> m >> q;
  fill_n(reps, n, -1);
  for (I i = 0; i < n; i++)
    pars[i] = {i, -1};
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    uni(a - 1, b - 1);
    day++;
  }
  for (I i = 0; i < n; i++)
    bld(i);
  while (q--) {
    I a, b;
    cin >> a >> b;
    printf("%i\n", qry(a - 1, b - 1));
  }
  return 0;
}