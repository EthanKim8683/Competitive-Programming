#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
const I T=10;
Lli dp[N+1][T+1][T-1+1][4][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,t;cin>>n>>t;
  for(I x=0;x<4;x++)for(I y=0;y<4;y++){
    if(y<x)dp[1][0][0][y][1]+=1;
    if(y>x)dp[1][0][0][y][0]+=1;
  }
  for(I i=2;i<n;i++)for(I j=0;j<=t;j++)for(I k=0;k<=t-1;k++)for(I x=0;x<4;x++)for(I y=0;y<4;y++){
    if(y<x)dp[i][j+1][k][y][1]+=dp[i-1][j][k][x][0];
    if(y<x)dp[i][j][k][y][1]+=dp[i-1][j][k][x][1];
    if(y>x)dp[i][j][k+1][y][0]+=dp[i-1][j][k][x][1];
    if(y>x)dp[i][j][k][y][0]+=dp[i-1][j][k][x][0];
  }
  Lli res=0;
  for(I i=0;i<4;i++)for(I j=0;j<2;j++)res+=dp[n-1][t][t-1][i][j];
  printf("%lli\n",res);
}