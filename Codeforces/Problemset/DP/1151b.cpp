#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=500;
const I M=500;
const I L=10;

I cels[N][M];
I dp[N][2];
I pars[N][2];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>cels[i][j];
  B res=0;
  for(I i=0;i<L;i++){
    fill(&dp[0][0],&dp[0][0]+N*2,-1);
    for(I j=0;j<m;j++)dp[0][cels[0][j]>>i&1]=j;
    for(I j=0;j+1<n;j++)for(I k=0;k<2;k++){
      if(dp[j][k]==-1)continue;
      for(I l=0;l<m;l++){
        I msk=k^(cels[j+1][l]>>i&1);
        dp[j+1][msk]=l,pars[j+1][msk]=k;
      }
    }
    if(dp[n-1][1]==-1)continue;
    I k=1;
    for(I j=n-1;j>=0;j--)ress[j]=dp[j][k],k=pars[j][k];
    printf("TAK\n");
    for(I j=0;j<n;j++)printf("%i ",ress[j]+1);
    exit(0);
  }
  printf("NIE");
}