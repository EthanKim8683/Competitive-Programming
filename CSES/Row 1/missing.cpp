// start 8:40
// end 8:42
// tries 2

#include <iostream>
#include <cstdio>

using namespace std;

using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("missing.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  Llu n;
  cin >> n;
  Llu s = (n * (n + 1)) / 2;
  while (--n) {
    Llu a;
    cin >> a;
    s -= a;
  }
  printf("%u\n", s);
  return 0;
}