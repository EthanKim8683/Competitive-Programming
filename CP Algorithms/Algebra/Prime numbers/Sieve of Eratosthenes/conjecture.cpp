#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 10000000;

vector<Lli> prms;
B coms[N];
B cnjs[N];

Lli cnj(Lli x, Lli y) {
  return x * x + y * y * y * y;
}

I cnt(I i) {
  return upper_bound(prms.begin(), prms.end(), i) - prms.begin();
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  coms[0] = true;
  coms[1] = true;
  for (I i = 2; i * i < N; i++)
    if (!coms[i])
      for (I j = i * i; j < N; j += i)
        coms[j] = true;
  for (I x = 0; cnj(x, 0) < N; x++)
    for (I y = 0; cnj(x, y) < N; y++)
      cnjs[cnj(x, y)] = true;
  for (I i = 0; i < N; i++)
    if (!coms[i] && cnjs[i])
      prms.push_back(i);
  while (t--) {
    I n;
    cin >> n;
    printf("%i\n", cnt(n));
  }
  return 0;
}