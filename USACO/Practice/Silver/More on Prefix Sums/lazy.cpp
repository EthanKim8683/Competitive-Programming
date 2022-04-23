#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

U field[400][401];

int main(void) {
  freopen("lazy.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("lazy.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (U r = n; r--;) {
    U* row = field[r];
    U sum = 0;
    for (U c = 1; c <= n; c++) {
      U g;
      cin >> g;
      sum += g;
      row[c] = sum;
    }
  }
  U result = 0;
  for (I r = n; r--;) {
    for (I c = n; c--;) {
      U sum = 0;
      for (I i = -k; i <= k; i++) {
        U index = i + r;
        if (index < 0 || index >= n)
          continue;
        U* row = field[index];
        const I c_radius = k - abs(i);
        const I c_min = max(c - c_radius - 1, 0);
        const I c_max = min(c + c_radius, n);
        sum += row[c_max] - row[c_min];
      }
      result = max(result, sum);
    }
  }
  printf("%u\n", result);
  return 0;
}