#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;
using B = bool;

const I N = 5e4;

S strs[N];

B cmp(S a, S b) {
  return a + b < b + a;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> strs[i];
  sort(strs, strs + n, cmp);
  S res = "";
  for (I i = 0; i < n; i++)
    res += strs[i];
  printf("%s\n", res.c_str());
  return 0;
}