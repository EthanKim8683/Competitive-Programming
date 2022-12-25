#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 3e5;
const I MIN = -1e9;

I a_arr[N];
vector<I> adjs1[N];
pair<I, I> dp1[N][2];
vector<pair<I, I>> sta;
I adjs2[N];
I dp2[N];
B viss[N];
I sizs[N];
I len = 0;

void cmb(pair<I, I>& a, pair<I, I> b) {
  if (a.first < b.first || (a.first == b.first && a.second > b.second))
    a = b;
}

pair<I, I> mov(pair<I, I> a) {
  return {a.first - 1, a.second};
}

void dfs1(I a, I p = -1) {
  for (const auto b : adjs1[a]) {
    if (b == p)
      continue;
    dfs1(b, a);
    cmb(dp1[a][0], mov(dp1[b][0]));
    cmb(dp1[a][0], mov({a_arr[b], b}));
  }
}

void dfs2(I a, I p = -1) {
  pair<I, I> cur = {MIN, -1};
  for (const auto b : adjs1[a]) {
    if (b == p)
      continue;
    sta.push_back(cur);
    cmb(cur, mov(dp1[b][0]));
    cmb(cur, mov({a_arr[b], b}));
  }
  reverse(adjs1[a].begin(), adjs1[a].end());
  cur = {MIN, -1};
  for (const auto b : adjs1[a]) {
    if (b == p)
      continue;
    cmb(dp1[b][1], mov({a_arr[a], a}));
    cmb(dp1[b][1], mov(cur));
    cmb(dp1[b][1], mov(sta.back()));
    cmb(cur, mov(dp1[b][0]));
    cmb(cur, mov({a_arr[b], b}));
    sta.pop_back();
  }
  for (const auto b : adjs1[a]) {
    if (b == p)
      continue;
    cmb(dp1[b][1], mov(dp1[a][1]));
    dfs2(b, a);
  }
}

I dfs3(I a) {
  if (viss[a])
    return sizs[a];
  viss[a] = true;
  sizs[a] = len;
  dp2[len] = a;
  len++;
  return dfs3(adjs2[a]);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  Lli k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n - 1; i++) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs1[u].push_back(v);
    adjs1[v].push_back(u);
  }
  fill(&dp1[0][0], &dp1[0][0] + sizeof(dp1) / sizeof(pair<I, I>), pair<I, I>(MIN, -1));
  dfs1(0);
  dfs2(0);
  for (I i = 0; i < n; i++) {
    pair<I, I> cur = {MIN, -1};
    cmb(cur, dp1[i][0]);
    cmb(cur, dp1[i][1]);
    adjs2[i] = cur.second;
  }
  const I off = dfs3(0);
  I ind;
  if (k < off)
    ind = k;
  else
    ind = off + (k - off) % (len - off);
  printf("%i\n", dp2[ind] + 1);
  return 0;
}