#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[101];
U hist[26];
U goal[26];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("24.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  for (U i = 2; i--;) {
    cin >> s;
    U o = 0;
    while (true) {
      const auto c = s[o];
      if (!c)
        break;
      o++;
      hist[c - 'A']++;
    }
  }
  cin >> s;
  U o = 0;
  while (true) {
    const auto c = s[o];
    if (!c)
      break;
    o++;
    goal[c - 'A']++;
  }
  U i = 0;
  for (; i < 26; i++)
    if (hist[i] != goal[i])
      break;
  if (i == 26)
    printf("YES\n");
  else
    printf("NO\n");
  return 0;
}