/*
ID: ethanki1
TASK: ride
LANG: C++14
*/

#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using C = char;
using S = string;

const I MOD = 47;

I main(void) {
#ifndef ETHANKIM8683
  freopen("ride.in", "r", stdin);
  freopen("ride.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  S com;
  cin >> com;
  S grp;
  cin >> grp;
  I com_prd = 1;
  I grp_prd = 1;
  for (const auto chr : com)
    (com_prd *= chr - 'A' + 1) %= MOD;
  for (const auto chr : grp)
    (grp_prd *= chr - 'A' + 1) %= MOD;
  if (com_prd == grp_prd)
    printf("GO\n");
  else
    printf("STAY\n");
  return 0;
}