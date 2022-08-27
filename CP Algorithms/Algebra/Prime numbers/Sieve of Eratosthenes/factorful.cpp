#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;

const I A = 1e6;
const I N = 10;

I facs[A + 1];
vector<I> ffls[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  facs[1] = 0;
  for (I i = 2; i <= A; i++)
    if (facs[i] == 0)
      for (I j = i; j <= A; j += i)
        facs[j]++;
  for (I i = 0; i <= A; i++)
    if (facs[i] <= N)
      ffls[facs[i]].push_back(i);
  I t;
  cin >> t;
  while (t--) {
    I a, b, n;
    cin >> a >> b >> n;
    const auto low = lower_bound(ffls[n].begin(), ffls[n].end(), a);
    const auto upp = upper_bound(ffls[n].begin(), ffls[n].end(), b);
    printf("%i\n", upp - low);
  }
  return 0;
}