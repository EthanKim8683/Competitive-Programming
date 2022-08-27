/*
ID: ethanki1
TASK: transform
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 10;

C oris[N][N + 1];
C pres[N][N + 1];
C trgs[N][N + 1];
C trns[N][N + 1];
I n;

void one() {
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      trns[j][n - i - 1] = pres[i][j];
}

void two() {
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      trns[n - i - 1][n - j - 1] = pres[i][j];
}

void thr() {
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      trns[n - j - 1][i] = pres[i][j];
}

void fou() {
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      trns[i][n - j - 1] = pres[i][j];
}

B cmp() {
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      if (trns[i][j] != trgs[i][j])
        return false;
  return true;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("transform.in", "r", stdin);
  freopen("transform.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> oris[i];
  for (I i = 0; i < n; i++)
    cin >> trgs[i];
  copy(&oris[0][0], &oris[0][0] + sizeof(oris) / sizeof(C), &pres[0][0]);
  one();
  if (cmp()) {
    printf("1\n");
    return 0;
  }
  two();
  if (cmp()) {
    printf("2\n");
    return 0;
  }
  thr();
  if (cmp()) {
    printf("3\n");
    return 0;
  }
  fou();
  if (cmp()) {
    printf("4\n");
    return 0;
  }
  copy(&trns[0][0], &trns[0][0] + sizeof(trns) / sizeof(C), &pres[0][0]);
  one();
  if (cmp()) {
    printf("5\n");
    return 0;
  }
  two();
  if (cmp()) {
    printf("5\n");
    return 0;
  }
  thr();
  if (cmp()) {
    printf("5\n");
    return 0;
  }
  if (cmp()) {
    printf("6\n");
    return 0;
  }
  printf("7\n");
  return 0;
}