#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=1000;
const I M=1000;
const I X=1000;
const I Y=1000;
const I MAX=1e9;

C cels[N][M+1];
I ps1[M+1],ps2[M+1];
I dp[M+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*2,MAX);
  I n,m,x,y;cin>>n>>m>>x>>y;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)ps1[i+1]+=cels[j][i]=='#';
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)ps2[i+1]+=cels[j][i]=='.';
  for(I i=0;i<m;i++)ps1[i+1]+=ps1[i],ps2[i+1]+=ps2[i];
  dp[0][0]=dp[0][1]=0;
  for(I i=0;i<m;i++)for(I j=x;j<=y&&i+j<=m;j++){
    dp[i+j][0]=min(dp[i+j][0],dp[i][1]+ps1[i+j]-ps1[i]);
    dp[i+j][1]=min(dp[i+j][1],dp[i][0]+ps2[i+j]-ps2[i]);
  }
  printf("%i\n",min(dp[m][0],dp[m][1]));
}