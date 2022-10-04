#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=3e5;
const Lli MIN=-1e18;

I a_arr[N];
Lli dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,q;cin>>n>>q;
    for(I i=0;i<=n;i++)dp[i][0]=0,dp[i][1]=MIN;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++){
      dp[i+1][1]=max(dp[i+1][1],dp[i][0]+a_arr[i]);
      dp[i+1][0]=max(dp[i+1][0],dp[i][1]-a_arr[i]);
      dp[i+1][0]=max(dp[i+1][0],dp[i][0]);
      dp[i+1][1]=max(dp[i+1][1],dp[i][1]);
    }
    printf("%lli\n",max(dp[n][0],dp[n][1]));
  }
}