#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U ks[10000];
U dp[10000][10000];

int main(void) {
  freopen("teamwork.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("teamwork.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  for (U i = 0; i < n; i++)
    cin >> ks[i];
  return 0;
}