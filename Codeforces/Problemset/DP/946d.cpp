#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=500;
const I M=500;
const I K=500;
const I MAX=1e9;
C cels[N][M+1];
I dp[M+1][K+1][3];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>cels[i];
  fill(&dp[0][0][0],&dp[0][0][0]+(M+1)*(K+1)*3,MAX);
  dp[0][0][0]=0;
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)for(I l=0;l<=k;l++){
      I o=l+cels[i][j]-'0';
      if(o<=k)cmb(dp[j+1][o][0],dp[j][l][0]);
      cmb(dp[j+1][l][1],dp[j][l][0]+1);
      cmb(dp[j+1][l][1],dp[j][l][1]+1);
      if(o<=k)cmb(dp[j+1][o][2],dp[j][l][0]);
      if(o<=k)cmb(dp[j+1][o][2],dp[j][l][1]);
      if(o<=k)cmb(dp[j+1][o][2],dp[j][l][2]);
    }
    for(I j=0;j<m;j++)for(I l=0;l<=k;l++)for(I o=0;o<3;o++)
      dp[j][l][o]=MAX;
    for(I j=0;j<=k;j++){
      cmb(dp[0][j][0],dp[m][j][0]);
      cmb(dp[0][j][0],dp[m][j][1]);
      cmb(dp[0][j][0],dp[m][j][2]);
      for(I l=0;l<3;l++)dp[m][j][l]=MAX;
    }
  }
  I res=MAX;
  for(I i=0;i<=k;i++)for(I j=0;j<3;j++)cmb(res,dp[0][i][j]);
  printf("%i\n",res);
}