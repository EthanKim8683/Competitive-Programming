#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 800;

C cels[N][N];
B tres[N][N];
B bees[N][N];
B viss[N][N];
queue<tuple<I, I, I>> bee_que;
stack<tuple<I, I, I>> rem_stk;
stack<tuple<I, I, I>> add_stk;
queue<tuple<I, I, I, I>> mec_que;
I n, s;
I mi, mj;
I di, dj;

B bnd(I i, I j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

void bee_vis(I i, I j, I tim) {
  if (!bnd(i, j))
    return;
  if (tres[i][j] || bees[i][j])
    return;
  if (i == di && j == dj)
    return;
  bees[i][j] = true;
  bee_que.push({i, j, tim});
  rem_stk.push({i, j, tim});
}

B mec_vis(I i, I j, I tim, I mid) {
  if (!bnd(i, j))
    return false;
  if (tres[i][j] || bees[i][j] || viss[i][j])
    return false;
  if (i == di && j == dj)
    return true;
  viss[i][j] = true;
  mec_que.push({i, j, tim + mid / s, mid % s});
  return false;
}

void set(I cur) {
  while (!rem_stk.empty()) {
    const auto [i, j, tim] = rem_stk.top();
    if (tim <= cur)
      break;
    rem_stk.pop();
    bees[i][j] = false;
    add_stk.push({i, j, tim});
  }
  while (!add_stk.empty()) {
    const auto [i, j, tim] = add_stk.top();
    if (tim > cur)
      break;
    add_stk.pop();
    bees[i][j] = true;
    rem_stk.push({i, j, tim});
  }
}

void fil() {
  while (!bee_que.empty()) {
    const auto [i, j, tim] = bee_que.front();
    bee_que.pop();
    bee_vis(i - 1, j, tim + 1);
    bee_vis(i + 1, j, tim + 1);
    bee_vis(i, j - 1, tim + 1);
    bee_vis(i, j + 1, tim + 1);
  }
}

B tes(I cur) {
  fill(&viss[0][0], &viss[0][0] + sizeof(viss) / sizeof(B), false);
  while (!mec_que.empty())
    mec_que.pop();
  set(cur);
  mec_vis(mi, mj, cur, 0);
  while (!mec_que.empty()) {
    const auto [i, j, tim, mid] = mec_que.front();
    mec_que.pop();
    if (cur != tim) {
      cur = tim;
      set(cur);
    }
    if (bees[i][j])
      continue;
    if (mec_vis(i - 1, j, tim, mid + 1))
      return true;
    if (mec_vis(i + 1, j, tim, mid + 1))
      return true;
    if (mec_vis(i, j - 1, tim, mid + 1))
      return true;
    if (mec_vis(i, j + 1, tim, mid + 1))
      return true;
  }
  return false;
}

I slv() {
  fil();
  I l = -1;
  I r = get<2>(rem_stk.top());
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (tes(m))
      l = m;
    else
      r = m - 1;
  }
  return l;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> s;
  for (I i = 0; i < n; i++)
    cin >> cels[i];
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      const C cel = cels[i][j];
      if (cel == 'T')
        tres[i][j] = true;
      else if (cel == 'M') {
        mi = i;
        mj = j;
      } else if (cel == 'D') {
        di = i;
        dj = j;
      } else if (cel == 'H')
        bee_vis(i, j, 0);
    }
  }
  printf("%i\n", slv());
  return 0;
}