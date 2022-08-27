#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I K = 3;
const I L = 19;

vector<I> dgts;
Lli pows[K + 1];
Lli facs[L + 1];

Lli pow(I x) {
  if (x < 0)
    return 0;
  return pows[x];
}

Lli bin(I n, I k) {
  if (n < 0 || k < 0 || n - k < 0)
    return 0;
  return facs[n] / (facs[k] * facs[n - k]);
}

void tod(Lli upp) {
  dgts.clear();
  for (; upp; upp /= 10)
    dgts.push_back(upp % 10);
  reverse(dgts.begin(), dgts.end());
}

pair<Lli, Lli> slv(Lli upp) {
  tod(upp);
  const I len = dgts.size();
  Lli res = 0;
  for (I i = 1; i < len; i++) {
    for (I j = 1; j < 10; j++) {
      for (I k = 1; k <= K; k++) {
        const I rem = len - i - 1;
        const I chs = k - (j != 0);
        res += pow(chs) * bin(rem, chs);
      }
    }
  }
  I cnt = 0;
  for (I i = 0; i < len; i++) {
    const I dgt = dgts[i];
    for (I j = i == 0; j < dgt; j++) {
      for (I k = 1; k <= K; k++) {
        const I rem = len - i - 1;
        const I chs = k - (j != 0) - cnt;
        res += pow(chs) * bin(rem, chs);
      }
    }
    cnt += dgt != 0;
  }
  return {res, cnt <= K};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  pows[0] = 1;
  for (I i = 1; i <= K; i++)
    pows[i] = pows[i - 1] * 9;
  facs[0] = 1;
  for (I i = 1; i <= L; i++)
    facs[i] = facs[i - 1] * i;
  I t;
  cin >> t;
  while (t--) {
    Lli l, r;
    cin >> l >> r;
    const auto [r_les, r_equ] = slv(r);
    const auto [l_les, l_equ] = slv(l);
    printf("%lli\n", r_les + r_equ - l_les);
  }
  return 0;
}