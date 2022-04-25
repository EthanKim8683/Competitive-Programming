#include <iostream>
#include <cstdio>

#define N 50

using namespace std;

using I = int;
using C = char;

C matrix[N][N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1360e.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    for (I i = 0; i < n; i++)
      cin >> matrix[i];
    for (I i = n; i--;)
      for (I j = n; j--;)
        if (matrix[i][j] == '1' &&
            j + 1 < n && matrix[i][j + 1] == '0' &&
            i + 1 < n && matrix[i + 1][j] == '0')
          goto NO;
    printf("YES\n");
    continue;
    NO:
    printf("NO\n");
  }
  return 0;
}