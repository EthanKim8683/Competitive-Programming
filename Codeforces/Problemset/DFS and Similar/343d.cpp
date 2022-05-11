#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 500000;
const I SEG = 1 << 20;

vector<I> adjs[N];
I emp_segs[SEG];
I fil_segs[SEG];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I n;

void dfs(I a, I p = -1) {
  tim_begs[a] = tim++;
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  tim_ends[a] = tim;
}

void emp_upd(I i, I val) {
  emp_segs[i += n] = val;
  for (; i > 1; i >>= 1)
    emp_segs[i >> 1] = max(emp_segs[i], emp_segs[i ^ 1]);
}

I emp_qry(I l, I r) {
  I res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res = max(res, emp_segs[l++]);
    if (r & 1)
      res = max(res, emp_segs[--r]);
  }
  return res;
}

void fil_upd(I l, I r, I val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      fil_segs[l++] = val;
    if (r & 1)
      fil_segs[--r] = val;
  }
}

I fil_qry(I i) {
  I res = 0;
  for (i += n; i > 0; i >>= 1)
    res = max(res, fil_segs[i]);
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("343d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = n; --i;) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  I q;
  cin >> q;
  for (I i = 1; i <= q; i++) {
    I c, v;
    cin >> c >> v;
    v--;
    const auto beg = tim_begs[v];
    const auto end = tim_ends[v];
    if (c == 1)
      fil_upd(beg, end, i);
    else if (c == 2)
      emp_upd(beg, i);
    else if (c == 3)
      printf("%i\n", fil_qry(beg) > emp_qry(beg, end));
  }
  return 0;
}