#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100000;
const I MIN=-1e9;

I dp[N+1][3][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*3*2,MIN);
  I n;cin>>n;
  S s;cin>>s;
  for(I i=0;i<n;i++){
    I c=s[i]-'0';
    dp[i+1][0][c]=max(dp[i+1][0][c],1);
    dp[i+1][0][0]=max(dp[i+1][0][0],dp[i][0][0]);
    dp[i+1][0][1]=max(dp[i+1][0][1],dp[i][0][1]);
    dp[i+1][1][0]=max(dp[i+1][1][0],dp[i][1][0]);
    dp[i+1][1][1]=max(dp[i+1][1][1],dp[i][1][1]);
    dp[i+1][2][0]=max(dp[i+1][2][0],dp[i][2][0]);
    dp[i+1][2][1]=max(dp[i+1][2][1],dp[i][2][1]);
    dp[i+1][0][c]=max(dp[i+1][0][c],dp[i][0][!c]+1);
    dp[i+1][1][!c]=max(dp[i+1][1][!c],dp[i][1][c]+1);
    dp[i+1][2][c]=max(dp[i+1][2][c],dp[i][2][!c]+1);
    dp[i+1][1][!c]=max(dp[i+1][1][!c],dp[i][0][c]+1);
    dp[i+1][2][c]=max(dp[i+1][2][c],dp[i][1][!c]+1);
  }
  I res=0;
  for(I i=0;i<=n;i++)for(I j=0;j<3;j++)for(I k=0;k<2;k++)res=max(res,dp[i][j][k]);
  printf("%i\n",res);
}