#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;
const I M = 1e5;
const I MAX = 1e9;

I a_arr[N];
pair<I, I> pais[M];
I cons[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m;
    cin >> n >> m;
    fill_n(cons, n, 0);
    for (I i = 0; i < n; i++)
      cin >> a_arr[i];
    for (I i = 0; i < m; i++) {
      I x, y;
      cin >> x >> y;
      x--;
      y--;
      pais[i] = {x, y};
      cons[x]++;
      cons[y]++;
    }
    if (m % 2 == 0) {
      printf("0\n");
      continue;
    }
    I res = MAX;
    for (I i = 0; i < n; i++)
      if (cons[i] % 2 == 1)
        res = min(res, a_arr[i]);
    for (I i = 0; i < m; i++) {
      const auto [x, y] = pais[i];
      if (cons[x] % 2 == 0 && cons[y] % 2 == 0)
        res = min(res, a_arr[x] + a_arr[y]);
    }
    printf("%i\n", res);
  }
  return 0;
}