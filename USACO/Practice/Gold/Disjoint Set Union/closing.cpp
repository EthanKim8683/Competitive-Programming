#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 200000;

vector<I> adjs[N];
I p_arr[N];
I pars[N];
I rnks[N];
B cons[N];
B ress[N];
I cnt = 0;

I fnd(I i) {
  if (pars[i] == -1)
    return i;
  return pars[i] = fnd(pars[i]);
}

void uni(I a, I b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b)
    return;
  if (rnks[a] < rnks[b]) {
    const auto t = a;
    a = b;
    b = t;
  }
  pars[b] = a;
  if (rnks[a] == rnks[b])
    rnks[a]++;
  cnt--;
}

I main(void) {
  freopen("closing.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("closing.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(pars, n, -1);
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for (I i = n - 1; i >= 0; i--) {
    I p;
    cin >> p;
    p_arr[i] = p - 1;
  }
  const I par = p_arr[0];
  for (I i = 0; i < n; i++) {
    const auto a = p_arr[i];
    cons[a] = true;
    cnt++;
    for (const auto b : adjs[a])
      if (cons[b])
        uni(a, b);
    ress[i] = cnt == 1;
  }
  for (I i = n - 1; i >= 0; i--) {
    if (ress[i])
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}