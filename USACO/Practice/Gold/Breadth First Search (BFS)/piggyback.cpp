#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX = 1e18;
const I N = 40000;
const I M = 40000;

vector<I> adjs[N];
queue<I> stts;
Lli b_arr[N];
Lli e_arr[N];
Lli p_arr[N];

void bfs(Lli arr[], I stp) {
  while (!stts.empty()) {
    const auto a = stts.front();
    stts.pop();
    for (const auto b : adjs[a]) {
      if (arr[b] == MAX) {
        arr[b] = arr[a] + stp;
        stts.push(b);
      }
    }
  }
}

I main(void) {
  freopen("piggyback.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("piggyback.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I b, e, p, n, m;
  cin >> b >> e >> p >> n >> m;
  fill_n(b_arr, n, MAX);
  fill_n(e_arr, n, MAX);
  fill_n(p_arr, n, MAX);
  for (I i = 0; i < m; i++) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  stts.push(0);
  b_arr[0] = 0;
  bfs(b_arr, b);
  stts.push(1);
  e_arr[1] = 0;
  bfs(e_arr, e);
  stts.push(n - 1);
  p_arr[n - 1] = 0;
  bfs(p_arr, p);
  Lli res = MAX;
  for (I i = 0; i < n; i++)
    res = min(res, b_arr[i] + e_arr[i] + p_arr[i]);
  printf("%lli\n", res);
  return 0;
}