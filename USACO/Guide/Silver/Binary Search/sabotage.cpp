#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using Lf = double;
using B = bool;

const I N = 100000;
const I M = 10000;
const I L = 100;
const Lf MIN = -1e9;

I m_arr[N];
Lf ps[N + 1];
Lli tot = 0;
I n;

B che(Lf ave) {
  ps[0] = 0;
  for (I i = 0; i < n; i++)
    ps[i + 1] = ps[i] + m_arr[i] - ave;
  Lf low = ps[1];
  Lf res = MIN;
  for (I i = 2; i < n; i++) {
    const Lf upp = ps[i];
    res = max(res, upp - low);
    low = min(low, upp);
  }
  return res >= tot - ave * n;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("sabotage.in", "r", stdin);
  freopen("sabotage.out", "w", stdout);
#endif
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> m_arr[i];
  for (I i = 0; i < n; i++)
    tot += m_arr[i];
  Lf l = 0;
  Lf r = M;
  for (I i = 0; i < L; i++) {
    const Lf m = (l + r) / 2;
    if (che(m))
      r = m;
    else
      l = m;
  }
  printf("%.3lf\n", (l + r) / 2);
  return 0;
}