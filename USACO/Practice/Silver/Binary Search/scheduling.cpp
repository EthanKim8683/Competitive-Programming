#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 100000;
const I M = 1000000;

I days[M];
vector<I> reqs[N];
queue<I> que;
I n, m, d;

B tes(I cnt) {
  I siz = 0;
  for (I i = 0; i < n; i++) {
    if (!reqs[i].empty()) {
      siz += reqs[i].size() - 1;
      if (siz / cnt > d)
        return false;
      siz++;
    }
    siz -= min(siz, cnt);
  }
  if (siz > 0)
    return false;
  return true;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> d >> m;
  for (I i = 0; i < m; i++)
    cin >> days[i];
  for (I i = 0; i < m; i++)
    reqs[days[i] - 1].push_back(i + 1);
  I l = 1;
  I r = m;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (tes(m))
      r = m;
    else
      l = m + 1;
  }
  printf("%i\n", l);
  for (I i = 0; i < n; i++) {
    for (const auto req : reqs[i])
      que.push(req);
    for (I j = 0; j < l && !que.empty(); j++) {
      printf("%i ", que.front());
      que.pop();
    }
    printf("0\n");
  }
  return 0;
}