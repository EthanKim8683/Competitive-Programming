#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;

U perm[5] = {0, 1, 2, 3, 4};
U adjs[5][5];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("65.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  for (U i = 0; i < 5; i++)
    for (U j = 0; j < 5; j++)
      cin >> adjs[i][j];
  U result = 0;
  do {
    U sum = 0;
    for (U i = 4; i--;) {
      for (U a = i; a < 4; a += 2) {
        const U a_perm = perm[a];
        const U b_perm = perm[a + 1];
        sum += adjs[a_perm][b_perm] + adjs[b_perm][a_perm];
      }
    }
    result = max(result, sum);
  } while (next_permutation(perm, perm + 5));
  printf("%u\n", result);
  return 0;
}