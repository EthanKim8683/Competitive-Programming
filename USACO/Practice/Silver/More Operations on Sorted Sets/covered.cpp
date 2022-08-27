#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

map<Lli, I> poss;
Lli cnts[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    Lli l, r;
    cin >> l >> r;
    poss[l]++;
    poss[r + 1]--;
  }
  Lli lst = -1;
  I cnt = 0;
  for (const auto [nxt, chg] : poss) {
    if (lst != -1)
      cnts[cnt] += nxt - lst;
    lst = nxt;
    cnt += chg;
  }
  for (I i = 1; i <= n; i++)
    printf("%lli ", cnts[i]);
  return 0;
}