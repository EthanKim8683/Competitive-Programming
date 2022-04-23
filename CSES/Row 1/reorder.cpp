// start 10:01
// end 10:08
// tries 1

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using S = string;
using C = char;

U counts[26];
C result[1000001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("reorder.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  S s;
  cin >> s;
  for (const C c : s)
    counts[c - 'A']++;
  const U k = s.length();
  const U b = k & 1;
  U l = 0;
  U r = k;
  C m = 0;
  for (C x = 0; x < 26; x++) {
    const C c = x + 'A';
    U o = counts[x];
    if (o & 1) {
      if (!b || m) {
        printf("NO SOLUTION");
        return 0;
      }
      m = c;
    }
    for (U o = counts[x] >> 1; o--;) {
      result[l++] = c;
      result[--r] = c;
    }
  }
  if (b)
    result[l] = m;
  printf("%s\n", result);
  return 0;
}