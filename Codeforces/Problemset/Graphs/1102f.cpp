#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=16;
const I M=1e4;
const I MAX=1e9;

I mats[N][M];
I dp[N][1<<N][N];
I diss1[N][N],diss2[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>mats[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    I dis1=MAX,dis2=MAX;
    for(I k=0;k<m;k++)dis1=min(dis1,abs(mats[i][k]-mats[j][k]));
    for(I k=0;k+1<m;k++)dis2=min(dis2,abs(mats[i][k]-mats[j][k+1]));
    diss1[i][j]=dis1,diss2[i][j]=dis2;
  }
  I res=0;
  for(I i=0;i<n;i++){
    dp[i][1<<i][i]=MAX;
    for(I j=0;j<(1<<n);j++)for(I k=0;k<n;k++)for(I l=0;l<n;l++)if(!(j>>l&1))
      dp[i][j|1<<l][l]=max(dp[i][j|1<<l][l],min(dp[i][j][k],diss1[k][l]));
    for(I j=0;j<n;j++)res=max(res,min(dp[i][(1<<n)-1][j],diss2[j][i]));
  }
  printf("%i\n",res);
}