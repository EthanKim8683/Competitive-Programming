#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I MIN=-1e9;

I a_arr[N];
I dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill(&dp[0][0],&dp[0][0]+(N+1)*2,MIN);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i],p=abs(a)%2;
    dp[i+1][p]=max(dp[i+1][p],a);
    dp[i+1][p]=max(dp[i+1][p],dp[i][0]+a);
    dp[i+1][!p]=max(dp[i+1][!p],dp[i][1]+a);
    dp[i+1][0]=max(dp[i+1][0],dp[i][0]);
    dp[i+1][1]=max(dp[i+1][1],dp[i][1]);
  }
  printf("%i\n",dp[n][1]);
}