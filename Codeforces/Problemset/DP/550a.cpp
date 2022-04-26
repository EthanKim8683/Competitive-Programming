#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 1e5;

C s[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("550a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  const I n = strlen(s);
  I bab = 0;
  I ab = 0;
  I ba = 0;
  for (I i = 0; i + 1 < n; i++) {
    const auto a = s[i];
    const auto b = s[i + 1];
    if (i + 2 < n) {
      const auto c = s[i + 2];
      if (a == 'A' && b == 'B' && c == 'A') {
        bab++;
        i += 2;
      } else if (a == 'B' && b == 'A' && c == 'B') {
        bab++;
        i += 2;
      } else if (a == 'A' && b == 'B') {
        ab++;
        i++;
      } else if (a == 'B' && b == 'A') {
        ba++;
        i++;
      }
    } else {
      if (a == 'A' && b == 'B') {
        ab++;
        i++;
      } else if (a == 'B' && b == 'A') {
        ba++;
        i++;
      }
    }
  }
  if (ab == 0 && bab > 0) {
    ab++;
    bab--;
  }
  if (ba == 0 && bab > 0) {
    ba++;
    bab--;
  }
  if (ab > 0 && ba > 0)
    printf("YES\n");
  else
    printf("NO\n");
  return 0;
}