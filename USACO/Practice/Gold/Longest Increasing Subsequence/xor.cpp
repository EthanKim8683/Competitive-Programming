#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;
const I LOGA = 9;
const I FIXA = 1 << 9;
const I MAX = 1e9;

I a_arr[N];
I dp[N + 1][FIXA];
vector<I> ress;

void cmb(I& a, I b) {
  a = min(a, b);
}

I main(void) {
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(I), MAX);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  dp[0][0] = 0;
  for (I i = 0; i < n; i++) {
    const I a = a_arr[i];
    for (I j = 0; j < FIXA; j++) {
      if (a > dp[i][j])
        cmb(dp[i + 1][j ^ a], a);
      cmb(dp[i + 1][j], dp[i][j]);
    }
  }
  for (I i = 0; i < FIXA; i++)
    if (dp[n][i] != MAX)
      ress.push_back(i);
  sort(ress.begin(), ress.end());
  printf("%i\n", ress.size());
  for (const auto res : ress)
    printf("%i ", res);
}