#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

I d_arr[N];
multiset<I> stks;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I x, n;
  cin >> x >> n;
  for (I i = 0; i < n; i++)
    cin >> d_arr[i];
  for (I i = 0; i < n; i++)
    stks.insert(d_arr[i]);
  Lli res = 0;
  for (I i = 0; i < n - 1; i++) {
    auto it = stks.begin();
    I sum = 0;
    sum += *it;
    it = stks.erase(it);
    sum += *it;
    it = stks.erase(it);
    res += sum;
    stks.insert(sum);
  }
  printf("%lli\n", res);
  return 0;
}