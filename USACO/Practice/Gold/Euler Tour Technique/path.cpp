#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

vector<I> adjs[N];
I v_arr[N];
Lli segs[N * 2];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I n;

void upd(I l, I r, I val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      segs[l++] += val;
    if (r & 1)
      segs[--r] += val;
  }
}

Lli qry(I i) {
  Lli res = 0;
  for (i += n; i > 0; i >>= 1)
    res += segs[i];
  return res;
}

void dfs(I a, I p = -1) {
  tim_begs[a] = tim++;
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  tim_ends[a] = tim;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("path.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> v_arr[i];
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  for (I i = 0; i < n; i++)
    upd(tim_begs[i], tim_ends[i], v_arr[i]);
  while (q--) {
    I t;
    cin >> t;
    if (t == 1) {
      I s, x;
      cin >> s >> x;
      s--;
      upd(tim_begs[s], tim_ends[s], x - v_arr[s]);
      v_arr[s] = x;
    } else if (t == 2) {
      I s;
      cin >> s;
      printf("%lli\n", qry(tim_begs[s - 1]));
    }
  }
  return 0;
}