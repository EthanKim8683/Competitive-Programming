#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using C = char;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("gsub.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    unordered_map<U, U> ps{{0, 1}};
    Llu result = 0;
    U sum = 0;
    while (n--) {
      C a;
      cin >> a;
      sum += a - '1';
      result += ps[sum];
      ps[sum]++;
    }
    printf("%llu\n", result);
  }
  return 0;
}