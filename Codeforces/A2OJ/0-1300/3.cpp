#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[51];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("3.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, t;
  cin >> n >> t;
  cin >> s;
  while (t--) {
    for (U i = 1; i < n; i++) {
      if (s[i] == 'G' && s[i - 1] == 'B') {
        s[i - 1] = 'G';
        s[i] = 'B';
        i++;
      }
    }
  }
  printf("%s\n", s);
  return 0;
}