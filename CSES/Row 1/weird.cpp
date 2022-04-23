// start 8:36
// end 8:38
// tries 2

#include <iostream>
#include <cstdio>

using namespace std;

using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("weird.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  Llu n;
  cin >> n;
  while (n != 1) {
    printf("%llu ", n);
    if (n & 1)
      n = n * 3 + 1;
    else
      n >>= 1;
  }
  printf("1\n");
  return 0;
}