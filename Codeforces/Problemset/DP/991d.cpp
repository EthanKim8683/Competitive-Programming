#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100;
const I MIN=-1e9;

I msks[N];
I dp[N+1][1<<2][1<<2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(1<<2)*(1<<2),MIN);
  S a;cin>>a;
  S b;cin>>b;
  I n=a.size();
  for(I i=0;i<n;i++)msks[i]=(a[i]=='X')<<1|(b[i]=='X')<<0;
  dp[0][0b11][0b11]=0;
  for(I i=0;i<n;i++){
    I t=msks[i];
    for(I j=0;j<(1<<2);j++)for(I k=0;k<(1<<2);k++){
      dp[i+1][k][t]=max(dp[i+1][k][t],dp[i][j][k]);
      if(k==0b01&&t==0b00)dp[i+1][0b11][0b11]=max(dp[i+1][0b11][0b11],dp[i][j][k]+1);
      if(k==0b10&&t==0b00)dp[i+1][0b11][0b11]=max(dp[i+1][0b11][0b11],dp[i][j][k]+1);
      if(k==0b00&&t==0b01)dp[i+1][0b11][0b11]=max(dp[i+1][0b11][0b11],dp[i][j][k]+1);
      if(k==0b00&&t==0b10)dp[i+1][0b11][0b11]=max(dp[i+1][0b11][0b11],dp[i][j][k]+1);
      if(k==0b00&&t==0b00){
        dp[i+1][0b10][0b11]=max(dp[i+1][0b10][0b11],dp[i][j][k]+1);
        dp[i+1][0b01][0b11]=max(dp[i+1][0b01][0b11],dp[i][j][k]+1);
        dp[i+1][0b11][0b10]=max(dp[i+1][0b11][0b10],dp[i][j][k]+1);
        dp[i+1][0b11][0b01]=max(dp[i+1][0b11][0b01],dp[i][j][k]+1);
      }
    }
  }
  I res=MIN;
  for(I i=0;i<(1<<2);i++)for(I j=0;j<(1<<2);j++)res=max(res,dp[n][i][j]);
  printf("%i\n",res);
}