#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;

const I N = 2e5;

set<I> lgts;
I p_arr[N];
I ress[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I x, n;
  cin >> x >> n;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  for (I i = 0; i < n; i++)
    lgts.insert(p_arr[i]);
  lgts.insert(0);
  lgts.insert(x);
  I res = 0;
  auto it = lgts.begin();
  while (true) {
    const I beg = *it++;
    if (it == lgts.end())
      break;
    const I end = *it;
    res = max(res, end - beg);
  }
  for (I i = n - 1; i >= 0; i--) {
    ress[i] = res;
    lgts.erase(p_arr[i]);
    auto it = lgts.upper_bound(p_arr[i]);
    const I end = *it--;
    const I beg = *it;
    res = max(res, end - beg);
  }
  for (I i = 0; i < n; i++)
    printf("%i ", ress[i]);
  return 0;
}