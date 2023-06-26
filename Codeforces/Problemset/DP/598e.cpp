#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=30;
const I K=50;
const Lli MAX=1e18;
Lli dp[N+1][N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*(K+1),MAX);
  for(I i=1;i<=N;i++)for(I j=1;j<=N;j++){
    dp[i][j][0]=0;
    if(i*j<=K)dp[i][j][i*j]=0;
    for(I k=0;k<=K;k++){
      for(I l=1;l<i;l++)for(I m=0;m<=k;m++)dp[i][j][k]=min(dp[i][j][k],dp[l][j][m]+dp[i-l][j][k-m]+j*j);
      for(I l=1;l<j;l++)for(I m=0;m<=k;m++)dp[i][j][k]=min(dp[i][j][k],dp[i][l][m]+dp[i][j-l][k-m]+i*i);
    }
  }
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    printf("%lli\n",dp[n][m][k]);
  }
}