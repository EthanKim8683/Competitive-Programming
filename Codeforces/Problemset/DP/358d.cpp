#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3000;
const I MIN=-1e9;
I a_arr[N];
I b_arr[N];
I c_arr[N];
I dp[N][4];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*3,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)cin>>c_arr[i];
  dp[0][0]=a_arr[0],dp[0][3]=b_arr[0];
  for(I i=1;i<n;i++){
    dp[i][0]=max(dp[i-1][3],dp[i-1][2])+a_arr[i];
    dp[i][1]=max(dp[i-1][0],dp[i-1][1])+b_arr[i];
    dp[i][2]=max(dp[i-1][1],dp[i-1][0])+c_arr[i];
    dp[i][3]=max(dp[i-1][2],dp[i-1][3])+b_arr[i];
  }
  printf("%i\n",max(dp[n-1][1],dp[n-1][0]));
}