#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I N = 2e5;

I k_arr[N];
vector<I> tows;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> k_arr[i];
  for (I i = 0; i < n; i++) {
    const I k = k_arr[i];
    const auto it = upper_bound(tows.begin(), tows.end(), k);
    if (it != tows.end())
      *it = k;
    else
      tows.push_back(k);
  }
  printf("%i\n", tows.size());
  return 0;
}