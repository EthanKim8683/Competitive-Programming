#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using Lli = long long int;

unordered_map<Lli, U> ps{{0, 1}};

int main(void) {
#if defined(ETHANKIM8683)
  freopen("sums2.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  Lli x;
  cin >> n >> x;
  Lli sum = 0;
  Llu result = 0;
  while (n--) {
    Lli a;
    cin >> a;
    sum += a;
    result += ps[sum - x];
    ps[sum]++;
  }
  printf("%llu\n", result);
  return 0;
}