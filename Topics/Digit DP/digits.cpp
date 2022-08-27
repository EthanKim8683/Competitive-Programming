#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using S = string;
using B = bool;

const I L = 19;

I a_arr[10];
Lli facs[L + 1];
I cnts[10];
vector<I> dgts;

Lli pow(Lli bse, Lli exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res *= bse;
    bse *= bse;
    exp >>= 1;
  }
  return res;
}

Lli bin(Lli n, Lli k) {
  return facs[n] / (facs[k] * facs[n - k]);
}

void tod(Lli val) {
  dgts.clear();
  while (val) {
    dgts.push_back(val % 10);
    val /= 10;
  }
  reverse(dgts.begin(), dgts.end());
}

pair<Lli, Lli> slv(Lli upp) {
  fill_n(cnts, 10, 0);
  tod(upp);
  const I len = dgts.size();
  Lli res = 0;
  for (I i = 1; i < len; i++) {
    for (I j = 1; j < 10; j++) {
      for (I k = 0; k < (1 << 10); k++) {
        Lli cnt = 1;
        I rem = len - i - 1;
        for (I l = 0; l < 10; l++) {
          if (k >> l & 1) {
            const I chs = a_arr[l] - (j == l);
            if (chs < 0 || rem - chs < 0) {
              cnt = 0;
              break;
            }
            cnt *= bin(rem, chs);
            rem -= chs;
          }
        }
        const I pop = __builtin_popcount(k);
        cnt *= pow(10 - pop, rem);
        res += pop % 2 ? -cnt : cnt;
      }
    }
  }
  for (I i = 0; i < len; i++) {
    for (I j = i == 0; j < dgts[i]; j++) {
      for (I k = 0; k < (1 << 10); k++) {
        Lli cnt = 1;
        I rem = len - i - 1;
        for (I l = 0; l < 10; l++) {
          if (k >> l & 1) {
            const I chs = a_arr[l] - (cnts[l] + (j == l));
            if (chs < 0 || rem - chs < 0) {
              cnt = 0;
              break;
            }
            cnt *= bin(rem, chs);
            rem -= chs;
          }
        }
        const I pop = __builtin_popcount(k);
        cnt *= pow(10 - pop, rem);
        res += pop % 2 ? -cnt : cnt;
      }
    }
    cnts[dgts[i]]++;
  }
  B equ = true;
  for (I i = 0; i < 10; i++)
    equ &= cnts[i] != a_arr[i];
  return {res, equ};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  facs[0] = 1;
  for (I i = 1; i <= L; i++)
    facs[i] = facs[i - 1] * i;
  I t;
  cin >> t;
  while (t--) {
    Lli a, b;
    cin >> a >> b;
    for (I i = 0; i < 10; i++)
      cin >> a_arr[i];
    const auto b_sol = slv(b);
    const auto a_sol = slv(a);
    printf("%lli\n", b_sol.first + b_sol.second - a_sol.first);
  }
  return 0;
}