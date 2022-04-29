#include <iostream>
#include <cstdio>
#include <unordered_set>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I K = 100;
const I A = 1e5;

I a_arr[A + 1];
I pows[A + 1][K];

I main(void) {
#ifdef ETHANKIM8683
  freopen("power.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    a_arr[a] = true;
  }
  for (I i = 2; i < A; i++) {
    Lli f = i;
    for (I j = 1; j < k && f < A; j++) {
      if (a_arr[f])
        pows[i][j] = true;
      f *= i;
    }
  }
  for (I i = 1; i < 7; i++) {
    for (I j = 1; j < k; j++)
      printf("%i ", pows[i][j]);
    printf("\n");
  }
  I res = 0;
  I j = 1;
  for (I i = k; --i; j++)
    for (I l = A; l--;)
      res += pows[l][i] && pows[l][j];
  printf("%i\n", res);
  return 0;
}