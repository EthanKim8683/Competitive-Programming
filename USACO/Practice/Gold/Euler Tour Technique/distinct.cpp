#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;

vector<I> adjs[N];
unordered_map<I, I> viss;
I c_arr[N];
I ress[N];
I fens[N + 1];
I tim_begs[N];
I tim_ends[N + 1];
I tim = 0;
I n;

void upd(I i, I val) {
  for (; i <= n; i += i & -i)
    fens[i] += val;
}

I qry(I i) {
  I res = 0;
  for (; i > 0; i -= i & -i)
    res += fens[i];
  return res;
}

void dfs(I a, I p = -1) {
  tim_begs[a] = tim;
  for (const auto b : adjs[a])
    if (b != p)
      dfs(b, a);
  tim_ends[++tim] = a;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("distinct.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> c_arr[i];
  for (I i = 0; i < n - 1; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  for (I i = 1; i <= n; i++) {
    const auto j = tim_ends[i];
    const auto col = c_arr[j];
    auto it = viss.find(col);
    if (it != viss.end()) {
      upd(it->second, -1);
      it->second = i;
    } else
      viss.insert({col, i});
    upd(i, 1);
    ress[j] = qry(i) - qry(tim_begs[j]);
  }
  for (I i = 0; i < n; i++)
    printf("%i ", ress[i]);
  return 0;
}