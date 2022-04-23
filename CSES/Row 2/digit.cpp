// start 10:25
// end 11:54
// tries 2

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

Llu p[18] = {
  1llu,
  10llu,
  100llu,
  1000llu,
  10000llu,
  100000llu,
  1000000llu,
  10000000llu,
  100000000llu,
  1000000000llu,
  10000000000llu,
  100000000000llu,
  1000000000000llu,
  10000000000000llu,
  100000000000000llu,
  1000000000000000llu,
  10000000000000000llu,
  100000000000000000llu
};
pair<Llu, U> k[1000];
U r[1000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("digit.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U q;
  cin >> q;
  for (U i = q; i--;) {
    auto& v = k[i];
    cin >> v.first;
    v.second = i;
  }
  sort(k, k + q);
  U n = 0;
  Llu l = 1llu;
  Llu u = 9llu;
  Llu e = 10llu;
  for (U i = 1; i < 18;) {
    while (true) {
      const auto [f, s] = k[n];
      if (f > u)
        break;
      const Llu d = f - l;
      const U m = i - d % i;
      r[s] = d / (Llu) i / p[m - 1] % 10llu + (Llu) (m == i);
      n++;
      if (n >= q)
        goto PRINT;
    }
    i++;
    l = u + 1llu;
    u += e * (Llu) i * 9llu;
    e *= 10llu;
  }
  PRINT:
  for (U i = q; i--;)
    printf("%u\n", r[i]);
  return 0;
}