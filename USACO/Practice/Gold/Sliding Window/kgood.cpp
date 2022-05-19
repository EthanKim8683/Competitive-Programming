#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

using I = int;

const I N = 5e5;

unordered_map<I, I> vals;
I a_arr[N];

void add(I i) {
  vals[i]++;
}

void rmv(I i) {
  if (--vals[i] == 0)
    vals.erase(i);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("kgood.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  I l = 0;
  I r = 0;
  I max_len = 0;
  I max_l, max_r;
  while (r <= n) {
    if (vals.size() > k)
      rmv(a_arr[l++]);
    else {
      const I len = r - l;
      if (len > max_len) {
        max_len = len;
        max_l = l;
        max_r = r;
      }
      if (r >= n)
        break;
      add(a_arr[r++]);
    }
  }
  printf("%i %i\n", max_l + 1, max_r);
  return 0;
}