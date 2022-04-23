#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C line[101];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("60.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U r = n; r--;) {
    const U r_bit = r & 1;
    cin >> line;
    for (U c = m; c--;) {
      auto& tile = line[c];
      if (tile == '.') {
        const U c_bit = c & 1;
        tile = r_bit ^ c_bit ? 'B' : 'W';
      }
    }
    printf("%s\n", line);
  }
  return 0;
}