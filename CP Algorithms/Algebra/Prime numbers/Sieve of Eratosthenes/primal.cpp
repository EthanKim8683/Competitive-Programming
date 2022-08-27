#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e6;
const I LOGN = 6;

I pows[LOGN + 2];
I coms[N];
vector<I> lovs;

I len(I x) {
  I l = 0;
  I r = LOGN;
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (x < pows[m])
      r = m - 1;
    else
      l = m;
  }
  return l + 1;
}

B tst(I x) {
  for (I i = len(x); i > 0; i--)
    if (coms[x % pows[i]] || x / pows[i - 1] % 10 == 0)
      return false;
  return true;
}

I cnt(I x) {
  return upper_bound(lovs.begin(), lovs.end(), x) - lovs.begin();
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  I pow = 1;
  for (I i = 0; i < LOGN + 2; i++) {
    pows[i] = pow;
    pow *= 10;
  }
  coms[0] = true;
  coms[1] = true;
  for (I i = 0; i * i < N; i++)
    if (!coms[i])
      for (I j = i * i; j < N; j += i)
        coms[j] = true;
  for (I i = 0; i < N; i++)
    if (tst(i))
      lovs.push_back(i);
  while (t--) {
    I n;
    cin >> n;
    printf("%i\n", cnt(n));
  }
  return 0;
}