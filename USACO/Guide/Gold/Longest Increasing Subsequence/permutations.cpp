#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;

const I N = 1e5;

I a_arr[N];
I b_arr[N];
I inds[N + 1];
vector<I> dp;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++)
    cin >> b_arr[i];
  for (I i = 0; i < n; i++)
    inds[a_arr[i]] = i;
  for (I i = 0; i < n; i++) {
    const I ind = inds[b_arr[i]];
    const auto it = lower_bound(dp.begin(), dp.end(), ind);
    if (it == dp.end())
      dp.push_back(ind);
    else
      *it = ind;
  }
  printf("%i\n", dp.size());
  return 0;
}