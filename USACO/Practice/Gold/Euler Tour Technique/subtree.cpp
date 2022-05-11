#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

vector<I> adjs[N];
I v_arr[N];
Lli segs[2 * N];
I tim_begs[N];
I tim_ends[N];
I tim = 0;
I n;

void set(I i, I val) {
  segs[n + i] = val;
}

void bld() {
  for (I i = n - 1; i > 0; i--)
    segs[i] = segs[i << 1] + segs[i << 1 | 1];
}

void upd(I i, I val) {
  segs[i += n] = val;
  for (; i > 1; i >>= 1)
    segs[i >> 1] = segs[i] + segs[i ^ 1];
}

Lli qry(I l, I r) {
  Lli res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res += segs[l++];
    if (r & 1)
      res += segs[--r];
  }
  return res;
}

void dfs(I a, I par = -1) {
  tim_begs[a] = tim;
  set(tim, v_arr[a]);
  tim++;
  for (const auto b : adjs[a])
    if (b != par)
      dfs(b, a);
  tim_ends[a] = tim;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("subtree.in", "r", stdin);
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
  bld();
  while (q--) {
    I t;
    cin >> t;
    if (t == 1) {
      I s, x;
      cin >> s >> x;
      upd(tim_begs[s - 1], x);
    } else if (t == 2) {
      I s;
      cin >> s;
      s--;
      printf("%lli\n", qry(tim_begs[s], tim_ends[s]));
    }
  }
  return 0;
}