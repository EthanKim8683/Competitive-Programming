#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;
using S = string;
using C = char;
using Lli = long long int;

const I N = 1e5;
const I MAX = 2e9;

Lli tot1 = 0;
Lli tot2 = 0;
I x1, y1;
I x2, y2;
I n;
S s;

B tes(I len) {
  Lli x = x1 + tot1 * len;
  Lli y = y1 + tot2 * len;
  for (I i = 0; i < n; i++) {
    if (abs(x - x2) + abs(y - y2) <= (Lli) n * len + i)
      return true;
    const C chr = s[i];
    x += (chr == 'R') - (chr == 'L');
    y += (chr == 'U') - (chr == 'D');
  }
  if (abs(x - x2) + abs(y - y2) <= (Lli) n * len + n)
    return true;
  return false;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> x1 >> y1;
  cin >> x2 >> y2;
  cin >> n;
  cin >> s;
  for (I i = 0; i < n; i++) {
    const C chr = s[i];
    tot1 += (chr == 'R') - (chr == 'L');
    tot2 += (chr == 'U') - (chr == 'D');
  }
  I l = 0;
  I r = MAX + 1;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (tes(m))
      r = m;
    else
      l = m + 1;
  }
  if (l == MAX + 1) {
    printf("-1\n");
    return 0;
  }
  Lli x = x1 + tot1 * l;
  Lli y = y1 + tot2 * l;
  I i = 0;
  for (; i < n; i++) {
    if (abs(x - x2) + abs(y - y2) <= (Lli) n * l + i)
      break;
    const C chr = s[i];
    x += (chr == 'R') - (chr == 'L');
    y += (chr == 'U') - (chr == 'D');
  }
  printf("%lli\n", (Lli) n * l + i);
  return 0;
}