#include <iostream>
#include <cstdio>
#include <numeric>

using namespace std;

using I = int;

const I N = 1e5;

I p_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    iota(p_arr, p_arr + n, 1);
    for (I i = n - 1; i - 1 >= 0; i -= 2)
      swap(p_arr[i], p_arr[i - 1]);
    for (I i = 0; i < n; i++)
      printf("%i ", p_arr[i]);
    printf("\n");
  }
  return 0;
}