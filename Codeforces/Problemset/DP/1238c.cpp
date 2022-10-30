#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;
const I MAX=1e9;

I p_arr[N+1];
I dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I h,n;cin>>h>>n;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    p_arr[n]=0;
    for(I i=0;i<=n;i++)dp[i][0]=dp[i][1]=MAX;
    dp[0][1]=0;
    for(I i=0;i+1<=n;i++){
      I a=p_arr[i],b=p_arr[i+1];
      if(a-b==1){
        dp[i+1][1]=min(dp[i+1][1],dp[i][0]);
        dp[i+1][0]=min(dp[i+1][0],dp[i][1]);
        dp[i+1][1]=min(dp[i+1][1],dp[i][1]+1);
      }else{
        dp[i+1][0]=min(dp[i+1][0],dp[i][0]+1);
        dp[i+1][0]=min(dp[i+1][0],dp[i][1]);
        dp[i+1][1]=min(dp[i+1][1],dp[i][1]+1);
      }
    }
    printf("%i\n",min(dp[n][1],dp[n][0]));
  }
}