#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1000;
const I M=1000;
const I K=10;
const I MIN=-1e9;
I dp[N+1][M+1][K+1][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0][0],&dp[0][0][0][0]+(N+1)*(M+1)*(K+1)*2,MIN);
  I n,m,k;cin>>n>>m>>k;
  S s;cin>>s;
  S t;cin>>t;
  dp[0][0][0][0]=0;
  for(I i=0;i<=n;i++)for(I j=0;j<=m;j++)for(I l=0;l<=k;l++){
    if(i<n&&j<m&&s[i]==t[j]){
      if(l+1<=k)dp[i+1][j+1][l+1][1]=max(dp[i+1][j+1][l+1][1],dp[i][j][l][0]+1);
      if(l+1<=k)dp[i+1][j+1][l+1][0]=max(dp[i+1][j+1][l+1][0],dp[i][j][l][0]+1);
      dp[i+1][j+1][l][1]=max(dp[i+1][j+1][l][1],dp[i][j][l][1]+1);
      dp[i+1][j+1][l][0]=max(dp[i+1][j+1][l][0],dp[i][j][l][1]+1);
    }
    if(i+1<=n)dp[i+1][j][l][0]=max(dp[i+1][j][l][0],dp[i][j][l][0]);
    if(j+1<=m)dp[i][j+1][l][0]=max(dp[i][j+1][l][0],dp[i][j][l][0]);
    if(i+1<=n)dp[i+1][j][l][0]=max(dp[i+1][j][l][0],dp[i][j][l][1]);
    if(j+1<=m)dp[i][j+1][l][0]=max(dp[i][j+1][l][0],dp[i][j][l][1]);
  }
  printf("%i\n",max(dp[n][m][k][0],dp[n][m][k][1]));
}