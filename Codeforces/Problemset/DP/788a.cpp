#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MIN=-1e18;

I a_arr[N];
Lli dp[N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)dp[i][1]=MIN;
  for(I i=0;i+1<n;i++)for(I j=0;j<2;j++)
    dp[i+1][!j]=max(dp[i+1][!j],dp[i][j]+abs(a_arr[i+1]-a_arr[i])*(j?-1:1));
  Lli res=MIN;
  for(I i=0;i<n;i++)for(I j=0;j<2;j++)res=max(res,dp[i][j]);
  printf("%lli\n",res);
}