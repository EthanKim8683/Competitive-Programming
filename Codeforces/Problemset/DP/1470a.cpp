#include <iostream>
#include <cstdio>
#include <algorithm>

#define N 300000

using namespace std;

using I = int;
using Lli = long long int;

I k_arr[N];
I c_arr[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1470a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m;
    cin >> n >> m;
    for (I i = n; i--;)
      cin >> k_arr[i];
    for (I i = 0; i < m; i++)
      cin >> c_arr[i];
    sort(k_arr, k_arr + n, greater<I>());
    I c_ptr = 0;
    Lli result = 0;
    for (I i = 0; i < n; i++) {
      const I k = k_arr[i] - 1;
      if (c_arr[c_ptr] < c_arr[k]) {
        result += c_arr[c_ptr];
        c_ptr++;
      } else
        result += c_arr[k];
    }
    printf("%lli\n", result);
  }
  return 0;
}