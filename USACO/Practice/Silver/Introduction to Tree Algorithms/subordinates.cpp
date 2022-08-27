#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I=int;

const I N=2e5;

vector<I> adjs[N];
I dp[N];

I dfs(I a, I p=-1) {
  dp[a]=1;
  for (const auto b : adjs[a])
    if (b!=p) dp[a]+=dfs(b, a);
  return dp[a];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i=1; i<n; i++) {
    I j;
    cin >> j;
    adjs[j-1].push_back(i);
  }
  dfs(0);
  for (I i=0; i<n; i++)
    printf("%i ", dp[i]-1);
  return 0;
}