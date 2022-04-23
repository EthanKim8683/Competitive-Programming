#include <iostream>
#include <cstdio>

using namespace std;

using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("37.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  Llu n, k;
  cin >> n >> k;
  const Llu m = n - n / 2llu;
  if (k > m)
    printf("%llu", (k - m) * 2llu);
  else
    printf("%llu", k * 2llu - 1llu);
  return 0;
}