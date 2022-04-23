#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("25.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k, l, c, d, p, nl, np;
  cin >> n >> k >> l >> c >> d >> p >> nl >> np;
  const U l_count = k * l / nl;
  const U d_count = c * d;
  const U p_count = p / np;
  printf("%u\n", min(l_count, min(d_count, p_count)) / n);
  return 0;
}