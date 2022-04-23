#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned;
using C = char;

C s[101];
C t[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("43.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  cin >> t;
  const U t_length = strlen(t);
  const U s_length = strlen(s);
  if (t_length == s_length) {
    U s_index = 0;
    for (U t_index = t_length; t_index--;) {
      if (s[s_index] != t[t_index])
        goto NO;
      s_index++;
    }
    printf("YES");
    return 0;
  }
  NO:
  printf("NO");
  return 0;
}