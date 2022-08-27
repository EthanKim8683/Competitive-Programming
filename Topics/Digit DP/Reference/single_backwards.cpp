#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I L = 10;
const I K = 9;

// 1. current index
// 2. trg count
// 3. x <= upp, x > upp
I dp[L + 1][K + 1][2];
vector<I> dgts;

void tod(I val) {
  dgts.clear();
  for (; val; val /= 10)
    dgts.push_back(val % 10);
}

I slv(I upp, I trg, I cnt) {
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(I), 0);
  tod(upp);
  const I len = dgts.size();
  dp[0][0][0] = 1;
  for (I i = 0; i < len; i++) {
    for (I j = 0; j <= cnt; j++) {
      for (I k = 0; k < 10; k++) {
        dp[i + 1][j + (k == trg)][k > dgts[i]] += dp[i][j][0];
        dp[i + 1][j + (k == trg)][k >= dgts[i]] += dp[i][j][1];
      }
    }
  }
  return dp[len][cnt][0];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I a, b, d, k;
  cin >> a >> b >> d >> k;
  printf("%i\n", slv(b, d, k) - slv(a - 1, d, k));
  return 0;
}