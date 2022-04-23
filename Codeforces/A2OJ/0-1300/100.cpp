#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[100001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("100.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U a, b, n;
  cin >> a >> b >> n;
  const U t = a;
  for (U i = 0; i < n; i++) {
    a = (a % b) * 10;
    const U d = (b - a % b) % b;
    if (d > 9) {
      printf("-1");
      return 0;
    }
    s[i] = d + '0';
    a += d;
  }
  printf("%u%s", t, s);
  return 0;
}