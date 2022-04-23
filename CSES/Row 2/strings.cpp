// start 8:27
// end 8:52
// tries 1

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

using U = unsigned;
using C = char;

C s[9];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("strings.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  const U n = strlen(s);
  sort(s, s + n);
  U f = n;
  for (U i = n; --i;)
    f *= i;
  C l = s[0];
  for (U i = 1; i < n; i++) {
    U d = 1;
    while (i < n) {
      const C t = s[i];
      if (t != l) {
        l = t;
        break;
      }
      d++;
      i++;
      f /= d;
    }
  }
  printf("%u\n", f);
  do
    printf("%s\n", s);
  while (next_permutation(s, s + n));
  return 0;
}