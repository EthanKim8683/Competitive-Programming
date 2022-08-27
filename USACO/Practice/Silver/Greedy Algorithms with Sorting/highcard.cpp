#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using B = bool;

const I N = 50000;

B uses[2 * N + 1];
I cars[N];
set<I> bes;

I main(void) {
#ifndef ETHANKIM8683
  freopen("highcard.in", "r", stdin);
  freopen("highcard.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> cars[i];
  for (I i = 0; i < n; i++)
    uses[cars[i]] = true;
  for (I i = 1; i <= 2 * n; i++)
    if (!uses[i])
      bes.insert(i);
  I res = 0;
  for (I i = 0; i < n; i++) {
    const I car = cars[i];
    const auto it = bes.upper_bound(car);
    if (it == bes.end())
      continue;
    bes.erase(it);
    res++;
  }
  printf("%i\n", res);
  return 0;
}