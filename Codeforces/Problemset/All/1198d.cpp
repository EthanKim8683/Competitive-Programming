#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=50;
const I MAX=1e9;
C grds[N][N+1];
I dp[N+1][N+1][N+1][N+1];
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0][0],&dp[0][0][0][0]+(N+1)*(N+1)*(N+1)*(N+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>grds[i];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)dp[i][i+1][j][j+1]=grds[i][j]=='#';
  for(I i=1;i<=n;i++)for(I j=1;j<=n;j++)for(I k=0;k+i<=n;k++)for(I l=0;l+j<=n;l++){
    for(I m=1;m<=i-1;m++)cmb(dp[k][k+i][l][l+j],dp[k][k+m][l][l+j]+dp[k+m][k+i][l][l+j]);
    for(I m=1;m<=j-1;m++)cmb(dp[k][k+i][l][l+j],dp[k][k+i][l][l+m]+dp[k][k+i][l+m][l+j]);
    cmb(dp[k][k+i][l][l+j],max(i,j));
  }
  printf("%i\n",dp[0][n][0][n]);
}
/*
two-dimensional range dp
*/