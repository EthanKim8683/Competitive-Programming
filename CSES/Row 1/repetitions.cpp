// start 8:42
// end 8:45
// tries 2

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using S = string;
using C = char;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("repetitions.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  S s;
  cin >> s;
  U m = 0;
  U k = 1;
  C l = 0;
  for (const C c : s) {
    if (c == l)
      k++;
    else {
      m = max(m, k);
      k = 1;
    }
    l = c;
  }
  m = max(m, k);
  printf("%u\n", m);
  return 0;
}