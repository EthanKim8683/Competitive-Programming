#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("game.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  Llu n;
  cin >> n;
  U result = 0;
  Llu i = 2;
  for (; i * i <= n; i++) {
    Llu factor = i;
    while (!(n % factor)) {
      result++;
      n /= factor;
      factor *= i;
    }
    while (!(n % i))
      n /= i;
  }
  result += n >= i;
  printf("%u\n", result);
  return 0;
}