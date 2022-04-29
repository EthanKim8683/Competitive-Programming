#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

using I = int;
using Lli = long long int;
using S = string;

const I N = 1e5;

unordered_map<S, I> strs;
I csts[N];
I pars[N];
I rnks[N];

I find(I a) {
  if (a == pars[a])
    return a;
  pars[a] = find(pars[a]);
  return pars[a];
}

void join(I a, I b) {
  a = find(a);
  b = find(b);
  if (a != b) {
    if (rnks[a] < rnks[b]) {
      const I t = a;
      a = b;
      b = t;
    }
    pars[b] = a;
    if (rnks[a] == rnks[b])
      rnks[a]++;
  }
  csts[a] = min(csts[a], csts[b]);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("959b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k, m;
  cin >> n >> k >> m;
  for (I i = 0; i < n; i++) {
    S str;
    cin >> str;
    strs[str] = i;
  }
  for (I i = 0; i < n; i++)
    cin >> csts[i];
  for (I i = 0; i < n; i++)
    pars[i] = i;
  while (k--) {
    I x;
    cin >> x;
    I a;
    cin >> a;
    while (--x) {
      I b;
      cin >> b;
      join(a - 1, b - 1);
    }
  }
  Lli res = 0;
  while (m--) {
    S str;
    cin >> str;
    res += csts[find(strs[str])];
  }
  printf("%lli\n", res);
  return 0;
}