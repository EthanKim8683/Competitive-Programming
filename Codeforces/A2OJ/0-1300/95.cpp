#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;

I matrix[10000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("95.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  I d;
  cin >> n >> m >> d;
  I length = n * m;
  for (U i = length; i--;)
    cin >> matrix[i];
  sort(matrix, matrix + length);
  const I median = matrix[length / 2];
  U result = 0;
  for (U i = length; i--;) {
    const auto a = matrix[i];
    const I diff = a - median;
    const I moves = diff / d;
    if (moves * d != diff) {
      printf("-1");
      return 0;
    }
    result += abs(moves);
  }
  printf("%u\n", result);
  return 0;
}