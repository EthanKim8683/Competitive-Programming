#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I SQTX = 10100;
const I X = SQTX * SQTX;
const I S = 2e5;

vector<I> prms;
B coms[SQTX + 1];
B curs[S];
vector<I> tots;
vector<I> ones;
vector<I> vals;

I len(I i) {
  return 32 - __builtin_clz(i);
}

I cnt(I i) {
  return __builtin_popcount(i);
}

I top(I i, I cnt) {
  return i >> (len(i) - cnt);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  for (I i = 2; i <= SQTX; i++) {
    if (!coms[i]) {
      prms.push_back(i);
      for (I j = i * i; j <= SQTX; j += i)
        coms[j] = true;
    }
  }
  tots.push_back(0);
  ones.push_back(0);
  curs[0] = true;
  curs[1] = true;
  for (I i = 0; i * S <= X; i++) {
    const I beg = i * S;
    for (const auto prm : prms)
      for (I j = max((beg + prm - 1) / prm, prm) * prm - beg; j < S; j += prm)
        curs[j] = true;
    for (I j = 0; j < S && beg + j <= X; j++) {
      if (!curs[j]) {
        const auto val = beg + j;
        tots.push_back(tots.back() + len(val));
        ones.push_back(ones.back() + cnt(val));
        vals.push_back(val);
      } else
        curs[j] = false;
    }
  }
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    const I ind = upper_bound(tots.begin(), tots.end(), n) - tots.begin() - 1;
    const I rmd = n - tots[ind];
    printf("%i\n", ones[ind] + cnt(top(vals[ind], rmd)));
  }
  return 0;
}