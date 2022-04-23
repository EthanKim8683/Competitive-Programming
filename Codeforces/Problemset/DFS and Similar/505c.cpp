#include <iostream>
#include <cstdio>
#include <map>

#define N 30001

using namespace std;

using I = int;
using B = bool;

multimap<I, pair<I, I>, greater<I>> states;
B gems[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("505c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, d;
  cin >> n >> d;
  for (I i = n; i--;) {
    I p;
    cin >> p;
    gems[p] = true;
  }
  states.insert({0, {0, d}});
  I result = 0;
  while (!states.empty()) {
    const auto it = states.begin();
    const auto [p, d] = it->second;
    const I c = it->first + gems[p];
    result = max(result, c);
    if (p + d < N)
      states.insert({c, {p + d, d}});
    if (p + d + 1 < N)
      states.insert({c, {p + d + 1, d + 1}});
    if (p + d - 1 < N && d > 1)
      states.insert({c, {p + d - 1, d - 1}});
    states.erase(it);
  }
  printf("%i\n", result);
  return 0;
}