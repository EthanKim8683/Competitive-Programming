#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I K=4;

I cels[N][K];
B dp[N+1][K+1][K/2+1][K/2+1][K/2+1][K/2+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)for(I j=0;j<k;j++)cin>>cels[i][j];
  dp[0][0][0][0][0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++){
    for(I a=0;a<=k/2;a++)for(I b=0;b<=k/2;b++)for(I c=0;c<=k/2;c++)for(I d=0;d<=k/2;d++){
      if(!dp[i][j][a][b][c][d])continue;
      dp[i+1][j][a][b][c][d]=1;
      if(j+1>k)continue;
      if(a+cels[i][0]>k/2)continue;
      if(b+cels[i][1]>k/2)continue;
      if(c+cels[i][2]>k/2)continue;
      if(d+cels[i][3]>k/2)continue;
      dp[i+1][j+1][a+cels[i][0]][b+cels[i][1]][c+cels[i][2]][d+cels[i][3]]=1;
    }
  }
  B res=0;
  for(I i=1;i<=k;i++)
    for(I a=0;a<=i/2;a++)for(I b=0;b<=i/2;b++)for(I c=0;c<=i/2;c++)for(I d=0;d<=i/2;d++)
      res|=dp[n][i][a][b][c][d];
  printf("%s\n",res?"YES":"NO");
}