#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using B = bool;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("9.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  Llu n;
  cin >> n;
  U count = 0;
  while (n) {
    const U digit = n % 10;
    count += digit == 7 || digit == 4;
    n /= 10;
  }
  B result = !!count;
  while (result && count) {
    const U digit = count % 10;
    result &= digit == 7 || digit == 4;
    count /= 10;
  }
  if (result)
    printf("YES");
  else
    printf("NO");
  return 0;
}