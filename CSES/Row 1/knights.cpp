// start 9:10
// end 9:24
// tries 

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("knights.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  Llu a = 5;
  Llu b = 1;
  Llu c = 0;
  while (n--) {
    printf("%llu\n", a * b * c);
    a++;
    b += c;
    c++;
  }
  return 0;
}