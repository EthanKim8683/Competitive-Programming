/*
ID: ethanki1
TASK: milk
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I M = 5000;

pair<I, I> frms[M];

I main(void) {
#ifndef ETHANKIM8683
  freopen("milk.in", "r", stdin);
  freopen("milk.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I p, a;
    cin >> p >> a;
    frms[i] = {p, a};
  }
  sort(frms, frms + m);
  I tot = 0;
  Lli cst = 0;
  for (I i = 0; i < m; i++) {
    I p, a;
    tie(p, a) = frms[i];
    I dif = min(n - tot, a);
    tot += dif;
    cst += dif * p;
  }
  printf("%lli\n", cst);
  return 0;
}