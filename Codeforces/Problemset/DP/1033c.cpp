#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I dp[N][2];
I invs[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)invs[a_arr[i]-1]=i;
  for(I i=n-1;i>=0;i--){
    I inv=invs[i];
    dp[inv][0]=1,dp[inv][1]=0;
    for(I j=inv;j<n;j+=i+1){
      if(a_arr[j]<=i+1)continue;
      if(dp[j][0]==1)dp[inv][1]=1;
      if(dp[j][1]==0)dp[inv][0]=0;
    }
    for(I j=inv;j>=0;j-=i+1){
      if(a_arr[j]<=i+1)continue;
      if(dp[j][0]==1)dp[inv][1]=1;
      if(dp[j][1]==0)dp[inv][0]=0;
    }
  }
  for(I i=0;i<n;i++)printf("%c",dp[i][0]+'A');
}