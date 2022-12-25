#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using S = string;

U ps[2019] = { 1 };

int main(void) {
#if defined(ETHANKIM8683)
  freopen("mul2019.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  S s;
  cin >> s;
  U result = 0;
  U sum = 0;
  U exp = 1;
  for (U i = s.length(); i--;) {
    sum = (sum + (s[i] - '0') * exp) % 2019;
    exp = exp * 10 % 2019;
    result += ps[sum];
    ps[sum]++;
  }
  printf("%u\n", result);
  return 0;
}