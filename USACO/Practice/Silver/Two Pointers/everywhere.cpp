#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using C = char;
using S = string;

const I N = 100000;
const I MAX = 1e9;

I dgts[N];
I cnts[2 * 26];
I cnt = 0;

I tod(C chr) {
  return chr >= 'a' ? chr - 'a' : chr - 'A' + 26;
}

void add(I val) {
  if (cnts[val]++ == 0)
    cnt++;
}

void rem(I val) {
  if (--cnts[val] == 0)
    cnt--;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  S s;
  cin >> s;
  for (I i = 0; i < s.size(); i++) {
    dgts[i] = tod(s[i]);
    add(dgts[i]);
  }
  const I tot = cnt;
  fill_n(cnts, 2 * 26, 0);
  cnt = 0;
  I res = MAX;
  I l = 0;
  I r = 0;
  add(dgts[0]);
  if (cnt == tot)
    res = min(res, r - l + 1);
  while (l < r || r < n - 1) {
    if (r == n - 1)
      rem(dgts[l++]);
    else if (l == r)
      add(dgts[++r]);
    else if (cnt >= tot)
      rem(dgts[l++]);
    else if (cnt < tot)
      add(dgts[++r]);
    if (cnt == tot)
      res = min(res, r - l + 1);
  }
  printf("%i\n", res);
  return 0;
}