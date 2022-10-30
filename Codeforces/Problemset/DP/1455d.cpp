#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=500;
const I A=500;
const I X=500;
const I MAX=1e9;

I a_arr[N];
I dp[N+1][A+1][X+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x;cin>>n>>x;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=A;j++)for(I k=0;k<=X;k++)dp[i][j][k]=MAX;
    dp[0][0][x]=0;
    for(I i=0;i<n;i++)for(I j=0;j<=A;j++)for(I k=0;k<=X;k++){
      I a=a_arr[i];
      if(a>=j)dp[i+1][a][k]=min(dp[i+1][a][k],dp[i][j][k]);
      if(k>=j&&a>=k)dp[i+1][k][a]=min(dp[i+1][k][a],dp[i][j][k]+1);
    }
    I res=MAX;
    for(I i=0;i<=A;i++)for(I j=0;j<=X;j++)res=min(res,dp[n][i][j]);
    printf("%i\n",res==MAX?-1:res);
  }
}