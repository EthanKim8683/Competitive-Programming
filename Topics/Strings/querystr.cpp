#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;

const I N = 1000000;

I zvls[N];

void zfn(S str) {
  const I len = str.size();
  fill_n(zvls, len, 0);
  zvls[0] = len;
  I l = 0;
  I r = 0;
  for (int i = 1; i < len; ++i) {
    if (i <= r)
      zvls[i] = min(r - i + 1, zvls[i - l]);
    while (i + zvls[i] < len && str[i + zvls[i]] == str[zvls[i]])
      zvls[i]++;
    if (i + zvls[i] - 1 > r) {
      l = i;
      r = i + zvls[i] - 1;
    }
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    S s;
    cin >> s;
    I n;
    cin >> n;
    reverse(s.begin(), s.end());
    zfn(s);
    const I len = s.size();
    while (n--) {
      I x;
      cin >> x;
      printf("%i\n", zvls[len - x]);
    }
  }
  return 0;
}