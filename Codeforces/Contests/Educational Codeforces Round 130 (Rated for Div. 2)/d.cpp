#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using C = char;
using B = bool;
using S = string;

const I N = 1000;

C lin[2];
C res[N + 1];
vector<I> unqs[26];

C qry(I i) {
  printf("? 1 %i\n", i + 1);
  fflush(stdout);
  cin >> lin;
  if (lin[0] == '0')
    exit(0);
  return lin[0];
}

I rng(I l, I r) {
  printf("? 2 %i %i\n", l + 1, r + 1);
  fflush(stdout);
  I res;
  cin >> res;
  if (res == 0)
    exit(0);
  return res;
}

I unq(I l, I r) {
  I res = 0;
  for (I i = 0; i < 26; i++) {
    const auto l_it = lower_bound(unqs[i].begin(), unqs[i].end(), l);
    const auto r_it = lower_bound(unqs[i].begin(), unqs[i].end(), r + 1);
    res += !!(r_it - l_it);
  }
  return res;
}

B inc(I i, I j) {
  return rng(i, j) == unq(i, j - 1);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I l = -1;
    I r = i - 1;
    while (l < r) {
      const I m = l + (r - l + 1) / 2;
      if (inc(m, i)) {
        l = m;
      } else
        r = m - 1;
    }
    if (l == -1)
      res[i] = qry(i);
    else
      res[i] = res[l];
    unqs[res[i] - 'a'].push_back(i);
  }
  printf("! %s\n", res);
  return 0;
}