#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;
const I MAX=1e9;

I a_arr[N-1];
I b_arr[N-1];
I ps1[N],ps2[N];
I dp[N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,c;cin>>n>>c;
  for(I i=0;i<n-1;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++)cin>>b_arr[i];
  fill(&dp[0][0],&dp[0][0]+N*2,MAX);
  dp[0][0]=0;
  for(I i=0;i+1<n;i++){
    dp[i+1][0]=min(dp[i+1][0],dp[i][0]+a_arr[i]);
    dp[i+1][0]=min(dp[i+1][0],dp[i][1]+a_arr[i]);
    dp[i+1][1]=min(dp[i+1][1],dp[i][0]+b_arr[i]+c);
    dp[i+1][1]=min(dp[i+1][1],dp[i][1]+b_arr[i]);
  }
  for(I i=n-1;i>0;i--){
    dp[i-1][0]=min(dp[i-1][0],dp[i][0]+a_arr[i-1]);
    dp[i-1][0]=min(dp[i-1][0],dp[i][1]+a_arr[i-1]);
    dp[i-1][1]=min(dp[i-1][1],dp[i][0]+b_arr[i-1]+c);
    dp[i-1][1]=min(dp[i-1][1],dp[i][1]+b_arr[i-1]);
  }
  for(I i=0;i<n;i++)printf("%i ",min(dp[i][0],dp[i][1]));
}