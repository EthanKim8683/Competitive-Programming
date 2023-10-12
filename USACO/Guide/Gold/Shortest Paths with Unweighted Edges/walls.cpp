#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I M = 200;
const I N = 250;
const I L = 30;
const I MAX = 1e9;

I mems[L];
vector<I> regs[M];
vector<I> tows[N];
B viss[N][N];
I bors[N][N];
vector<I> adjs[M];
I diss[M];
I tots[M];
queue<I> que;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> m;
  I n;
  cin >> n;
  I l;
  cin >> l;
  for (I i = 0; i < l; i++) {
    I mem;
    cin >> mem;
    mems[i] = mem - 1;
  }
  for (I i = 0; i < m; i++) {
    I t;
    cin >> t;
    for (I j = 0; j < t; j++) {
      I tow;
      cin >> tow;
      tow--;
      regs[i].push_back(tow);
      tows[tow].push_back(i);
    }
  }
  for (I i = 0; i < m; i++) {
    for (I j = 0; j < regs[i].size(); j++) {
      const I a = regs[i][j];
      const I b = regs[i][(j + 1) % regs[i].size()];
      if (viss[b][a]) {
        const I bor = bors[b][a];
        adjs[i].push_back(bor);
        adjs[bor].push_back(i);
      }
      viss[a][b] = true;
      bors[a][b] = i;
    }
  }
  for (I i = 0; i < l; i++) {
    fill_n(diss, m, MAX);
    for (const auto reg : tows[mems[i]]) {
      diss[reg] = 0;
      que.push(reg);
    }
    while (!que.empty()) {
      const auto a = que.front();
      que.pop();
      const I dis = diss[a];
      for (const auto b : adjs[a]) {
        if (dis + 1 < diss[b]) {
          diss[b] = dis + 1;
          que.push(b);
        }
      }
    }
    for (I j = 0; j < m; j++)
      tots[j] += diss[j];
  }
  I cnt = MAX;
  I lab = -1;
  for (I i = 0; i < m; i++) {
    const I tot = tots[i];
    if (tot < cnt) {
      cnt = tot;
      lab = i;
    }
  }
  printf("%i\n%i\n", cnt, lab + 1);
  return 0;
}