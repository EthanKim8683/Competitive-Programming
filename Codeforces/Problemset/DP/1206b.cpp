#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

I a_arr[N];
Lli dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*2,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    for(I j=0;j<2;j++){
      dp[i+1][!j]=min(dp[i+1][!j],dp[i][j]+abs(-1-a));
      dp[i+1][j]=min(dp[i+1][j],dp[i][j]+abs(1-a));
    }
  }
  printf("%lli\n",dp[n][0]);
}