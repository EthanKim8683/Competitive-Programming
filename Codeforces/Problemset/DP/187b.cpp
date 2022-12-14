#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=60;
const I M=60;
const I K=1000;
const I MAX=1e9;
I diss[M][N][N];
I mins[N][N];
I dp[K+1][N][N];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&mins[0][0],&mins[0][0]+N*N,MAX);
  fill(&dp[0][0][0],&dp[0][0][0]+(K+1)*N*N,MAX);
  I n,m,r;cin>>n>>m>>r;
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++)cin>>diss[i][j][k];
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++)for(I l=0;l<n;l++)cmb(diss[i][k][l],diss[i][k][j]+diss[i][j][l]);
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++)cmb(mins[j][k],diss[i][j][k]);
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)dp[0][i][j]=mins[i][j];
  for(I i=0;i<K;i++){
    for(I j=0;j<n;j++)for(I k=0;k<n;k++)for(I l=0;l<n;l++)cmb(dp[i+1][k][l],dp[i][k][j]+mins[j][l]);
    for(I j=0;j<n;j++)for(I k=0;k<n;k++)cmb(dp[i+1][j][k],dp[i][j][k]);
  }
  while(r--){
    I s,t,k;cin>>s>>t>>k,s--,t--;
    printf("%i\n",dp[k][s][t]);
  }
}