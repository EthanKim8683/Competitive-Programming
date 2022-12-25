#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U ps[100001];

int main(void) {
  freopen("maxcross.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("maxcross.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k, b;
  cin >> n >> k >> b;
  while (b--) {
    U id;
    cin >> id;
    ps[id] = 1;
  }
  U sum = 0;
  for (U id = 1; id < k; id++) {
    sum += ps[id];
    ps[id] = sum;
  }
  U result = -1;
  U lo = 0;
  for (U hi = k; hi <= n; hi++) {
    sum += ps[hi];
    ps[hi] = sum;
    result = min(result, sum - ps[lo]);
    lo++;
  }
  printf("%u\n", result);
  return 0;
}