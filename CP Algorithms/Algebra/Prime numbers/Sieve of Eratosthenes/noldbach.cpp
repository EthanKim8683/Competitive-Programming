#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1000;

vector<I> prms;
B coms[N + 1];
vector<I> sums;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  coms[0] = true;
  coms[1] = true;
  for (I i = 2; i * i <= N; i++)
    if (!coms[i])
      for (I j = i * i; j <= N; j += i)
        coms[j] = true;
  for (I i = 0; i <= N; i++)
    if (!coms[i])
      prms.push_back(i);
  for (I i = 0; i + 1 < prms.size(); i++)
    sums.push_back(prms[i] + prms[i + 1] + 1);
  I n, k;
  cin >> n >> k;
  I cnt = 0;
  for (I i = 2; i <= n; i++)
    cnt += !coms[i] && find(sums.begin(), sums.end(), i) != sums.end();
  if (cnt >= k)
    printf("YES\n");
  else
    printf("NO\n");
  return 0;
}