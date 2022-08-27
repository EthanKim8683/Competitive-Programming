#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;
using Llu = long long unsigned;

const I N = 1000000007;
const I SQTN = 31622;
const I D = 1e6;
const I S = 300;
const Llu M = 1e18;
const Llu LOGM = 18;

B coms[SQTN + 1];
B curs[D + S + 1];
vector<I> prms;
Llu pows[LOGM + 1 + 1];

I len(Llu i) {
  I l = 0;
  I r = LOGM;
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (i >= pows[m])
      l = m;
    else
      r = m - 1;
  }
  return l + 1;
}

tuple<Lli, Lli, Lli> gcd(Lli a, Lli b) {
  Lli x = 1, y = 0, z = 0, w = 1;
  while (b) {
    const Lli q = a / b;
    tie(x, z) = make_pair(z, x - q * z);
    tie(y, w) = make_pair(w, y - q * w);
    tie(a, b) = make_pair(b, a - q * b);
  }
  return {x, y, a};
}

Llu inv(Lli i, Lli mod) {
  const auto [x, y, g] = gcd(i, mod);
  return x + (x < 0) * mod;
}

Llu slv(Llu p1, Llu p2) {
  // let m = 10 ^ len(p1)
  // p2 * x = p1 (mod m)
  // x = p1 * inv(p2) (mod m)
  const Llu m = pows[len(p1)];
  const Llu x = (p1 * inv(p2, m) % m);
  return p2 * x;
}

pair<Llu, Llu> add(Llu low, Llu hgh, Llu add) {
  low += add;
  hgh += low / M;
  low %= M;
  return {low, hgh};
}

void log(Llu low, Llu hgh) {
  if (hgh != 0) {
    printf("%llu", hgh);
    for (I j = len(low); j < LOGM; j++)
      printf("0");
  }
  printf("%llu\n", low);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  Llu pow = 1;
  for (I i = 0; i < LOGM + 1 + 1; i++) {
    pows[i] = pow;
    pow *= 10;
  }
  for (I i = 2; i <= SQTN; i++) {
    if (!coms[i]) {
      prms.push_back(i);
      for (I j = i * i; j <= SQTN; j += i)
        coms[j] = true;
    }
  }
  I t;
  cin >> t;
  while (t--) {
    I l, r;
    cin >> l >> r;
    const I len = r - l;
    for (const auto prm : prms)
      for (I i = max((l + prm - 1) / prm, prm) * prm - l; i <= len + S; i += prm)
        curs[i] = true;
    Llu low = 0;
    Llu hgh = 0;
    I lst = -1;
    for (I i = 0; i <= len + S; i++) {
      if (!curs[i]) {
        const I nxt = l + i;
        if (lst != -1) {
          tie(low, hgh) = add(low, hgh, slv(lst, nxt));
          if (i > len)
            break;
        }
        lst = nxt;
      } else
        curs[i] = false;
    }
    log(low, hgh);
  }
  return 0;
}