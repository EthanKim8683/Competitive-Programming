// start 9:05
// end 9:48
// tries 1

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using C = char;

C b[9][9];
U d = 0;

U dfs(Llu f) {
  if (d == 8)
    return 1;
  U k = 0;
  const C* bl = b[d];
  const Llu fl = f >> (d << 3) & 0xffllu;
  d++;
  for (U i = 8; i--;) {
    const Llu x = 1llu << i;
    if (!(fl & x) && bl[i] == '.') {
      Llu nf = f;
      Llu l = x << 1;
      Llu r = x >> 1;
      for (U o = d; o < 8; o++) {
        nf |= ((l | x | r) & 0xffllu) << (o << 3);
        l <<= 1;
        r >>= 1;
      }
      k += dfs(nf);
    }
  }
  d--;
  return k;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("queens.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  for (U i = 8; i--;)
    cin >> b[i];
  printf("%u\n", dfs(0));
  return 0;
}