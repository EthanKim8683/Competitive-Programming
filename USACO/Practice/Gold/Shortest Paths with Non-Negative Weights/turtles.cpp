#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using C = char;
using B = bool;
using S = string;

const I N = 8;
const I MAX = 1e9;

C row[N + 1];
C cels[N][N];
I dsts[N][N][4];
S sols[N][N][4];
priority_queue<tuple<I, I, I, I>, vector<tuple<I, I, I, I>>, greater<tuple<I, I, I, I>>> que;

I mod(I i) {
  return i % 4 + (i < 0) * 4;
}

pair<I, S> mov(I i, I j, I dir, I mov) {
  I cst = 0;
  S sol = sols[i][j][dir];
  const I lft = mod(dir - mov);
  const I rgt = mod(mov - dir);
  if (lft < rgt) {
    cst += lft;
    for (I k = 0; k < lft; k++)
      sol += 'L';
  } else {
    cst += rgt;
    for (I k = 0; k < rgt; k++)
      sol += 'R';
  }
  i += (mov == 1) - (mov == 3);
  j += (mov == 0) - (mov == 2);
  if (cels[i][j] == 'I') {
    cst++;
    sol += 'X';
  }
  sol += 'F';
  return {cst, sol};
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("turtles.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  for (I i = 0; i < N; i++)
    for (I j = 0; j < N; j++)
      fill_n(dsts[i][j], 4, MAX);
  I d_i, d_j;
  for (I i = 0; i < N; i++) {
    cin >> row;
    for (I j = 0; j < N; j++) {
      switch (row[j]) {
        case 'T':
          que.push({dsts[i][j][0] = 0, i, j, 0});
          break;
        case 'D':
          d_i = i;
          d_j = j;
        default:
          cels[i][j] = row[j];
          break;
      }
    }
  }
  while (!que.empty()) {
    const auto [dst, i, j, dir] = que.top();
    que.pop();
    if (dst == dsts[i][j][dir]) {
      if (j + 1 < N && cels[i][j + 1] != 'C') {
        const auto [cst, sol] = mov(i, j, dir, 0);
        if (dst + cst < dsts[i][j + 1][0]) {
          dsts[i][j + 1][0] = dst + cst;
          sols[i][j + 1][0] = sol;
          que.push({dsts[i][j + 1][0], i, j + 1, 0});
        }
      }
      if (i + 1 < N && cels[i + 1][j] != 'C') {
        const auto [cst, sol] = mov(i, j, dir, 1);
        if (dst + cst < dsts[i + 1][j][1]) {
          dsts[i + 1][j][1] = dst + cst;
          sols[i + 1][j][1] = sol;
          que.push({dsts[i + 1][j][1], i + 1, j, 1});
        }
      }
      if (j - 1 >= 0 && cels[i][j - 1] != 'C') {
        const auto [cst, sol] = mov(i, j, dir, 2);
        if (dst + cst < dsts[i][j - 1][2]) {
          dsts[i][j - 1][2] = dst + cst;
          sols[i][j - 1][2] = sol;
          que.push({dsts[i][j - 1][2], i, j - 1, 2});
        }
      }
      if (i - 1 >= 0 && cels[i - 1][j] != 'C') {
        const auto [cst, sol] = mov(i, j, dir, 3);
        if (dst + cst < dsts[i - 1][j][3]) {
          dsts[i - 1][j][3] = dst + cst;
          sols[i - 1][j][3] = sol;
          que.push({dsts[i - 1][j][3], i - 1, j, 3});
        }
      }
    }
  }
  I dst = MAX;
  S sol = "no solution";
  for (I i = 0; i < 4; i++) {
    if (dsts[d_i][d_j][i] < dst) {
      dst = dsts[d_i][d_j][i];
      sol = sols[d_i][d_j][i];
    }
  }
  printf("%s\n", sol.c_str());
  return 0;
}