#include <iostream>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using C = char;

const I N = 20;

B viss[N][N][N][N][4];
queue<tuple<I, I, I, I, I, I>> que;
B cels[N][N];
I n;

I mod(I i) {
  return i % 4 + (i < 0) * 4;
}

void mov(I a_i, I a_j, I b_i, I b_j, I dir, I dst, C mov) {
  if (mov == 'F' && (a_i != n - 1 || a_j != n - 1)) {
    const I a_k = a_i + (dir == 0) - (dir == 2);
    const I a_l = a_j + (dir == 1) - (dir == 3);
    if (a_k >= 0 && a_k < n && a_l >= 0 && a_l < n && !cels[a_k][a_l]) {
      a_i = a_k;
      a_j = a_l;
    }
  }
  if (mov == 'F' && (b_i != n - 1 || b_j != n - 1)) {
    const I b_k = b_i + (dir == 3) - (dir == 1);
    const I b_l = b_j + (dir == 0) - (dir == 2);
    if (b_k >= 0 && b_k < n && b_l >= 0 && b_l < n && !cels[b_k][b_l]) {
      b_i = b_k;
      b_j = b_l;
    }
  }
  dir = mod(dir + (mov == 'R') - (mov == 'L'));
  que.push({a_i, a_j, b_i, b_j, dir, dst + 1});
}

I main(void) {
  freopen("cownav.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("cownav.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = n - 1; i >= 0; i--) {
    for (I j = 0; j < n; j++) {
      C c;
      cin >> c;
      cels[i][j] = c == 'H';
    }
  }
  que.push({0, 0, 0, 0, 0, 0});
  while (!que.empty()) {
    const auto [a_i, a_j, b_i, b_j, dir, dst] = que.front();
    que.pop();
    if (!viss[a_i][a_j][b_i][b_j][dir]) {
      viss[a_i][a_j][b_i][b_j][dir] = true;
      if (a_i == n - 1 && a_j == n - 1 &&
          b_i == n - 1 && b_j == n - 1) {
        printf("%i\n", dst);
        break;
      }
      mov(a_i, a_j, b_i, b_j, dir, dst, 'L');
      mov(a_i, a_j, b_i, b_j, dir, dst, 'R');
      mov(a_i, a_j, b_i, b_j, dir, dst, 'F');
    }
  }
  return 0;
}