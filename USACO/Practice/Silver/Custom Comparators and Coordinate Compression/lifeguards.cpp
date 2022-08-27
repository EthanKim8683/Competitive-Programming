#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;
const Lli MAX = 1e18;

pair<I, I> rngs[N];
unordered_map<I, I> cpss;
I dcps[2 * N];
I tims[2 * N];
Lli a_ps[2 * N];
Lli b_ps[2 * N + 1];

I cps(I i) {
  auto it = cpss.find(i);
  if (it == cpss.end()) {
    dcps[cpss.size()] = i;
    it = cpss.insert({i, cpss.size()}).first;
  }
  return it->second;
}

I dcp(I i) {
  return dcps[i];
}

I main(void) {
  freopen("lifeguards.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("lifeguards.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, b;
    cin >> a >> b;
    rngs[i] = {a, b};
    tims[i * 2] = a;
    tims[i * 2 + 1] = b;
  }
  sort(tims, tims + 2 * n);
  for (I i = 0; i < 2 * n; i++)
    cps(tims[i]);
  for (I i = 0; i < n; i++) {
    const auto [a, b] = rngs[i];
    a_ps[cps(a)]++;
    a_ps[cps(b)]--;
  }
  for (I i = 0; i + 1 < cpss.size(); i++)
    a_ps[i + 1] += a_ps[i];
  I tot = 0;
  for (I i = 0; i < cpss.size(); i++) {
    const auto rng = dcp(i + 1) - dcp(i);
    tot += (a_ps[i] > 0) * rng;
    a_ps[i] = (a_ps[i] == 1) * rng;
  }
  for (I i = 0; i < cpss.size(); i++)
    b_ps[i + 1] = b_ps[i] + a_ps[i];
  Lli res = MAX;
  for (I i = 0; i < n; i++) {
    const auto [a, b] = rngs[i];
    res = min(res, b_ps[cps(b)] - b_ps[cps(a)]);
  }
  printf("%i\n", tot - res);
  return 0;
}