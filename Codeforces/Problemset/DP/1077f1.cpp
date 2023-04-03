#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200;
const I K=200;
const I X=200;
const Lli MIN=-1e18;
I a_arr[N];
Lli dp[N+1][X+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(K+1),MIN);
  I n,k,x;cin>>n>>k>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=0;
  for(I i=1;i<=n;i++)for(I j=1;j<=x;j++)for(I l=1;l<=k&&i-l>=0;l++)dp[i][j]=max(dp[i][j],dp[i-l][j-1]+a_arr[i-1]);
  Lli res=MIN;
  for(I i=0;i<=k-1&&n-i>=0;i++)res=max(res,dp[n-i][x]);
  printf("%lli\n",res<0?-1:res);
}