#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I L = 18;

Lli pows[L + 1];

I sum(Lli val) {
  I res = 0;
  for (; val; val /= 10)
    res += val % 10;
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  pows[0] = 1;
  for (I i = 1; i <= L; i++)
    pows[i] = pows[i - 1] * 10;
  I t;
  cin >> t;
  while (t--) {
    Lli n;
    I s;
    cin >> n >> s;
    I cur = sum(n);
    Lli res = 0;
    if (cur > s) {
      cur++;
      for (I i = 0; cur > s; i++) {
        cur -= n / pows[i] % pows[1];
        res = pows[i + 1] - n % pows[i + 1];
      }
    }
    printf("%lli\n", res);
  }
  return 0;
}