#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=1000;
const I M=1000;
const I MAX=1e9;
const I MIN=-MAX;
C mats[N][M+1];
I dp[N][M][4];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>mats[i];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)for(I k=0;k<4;k++)dp[i][j][k]=MIN;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      if(mats[i][j]=='B')dp[i][j][0]=max(dp[i][j][0],0);
      if(i+1<n)dp[i+1][j][0]=max(dp[i+1][j][0],dp[i][j][0]+1);
      if(j+1<m)dp[i][j+1][0]=max(dp[i][j+1][0],dp[i][j][0]+1);
    }
    for(I i=0;i<n;i++)for(I j=m-1;j>=0;j--){
      if(mats[i][j]=='B')dp[i][j][1]=max(dp[i][j][1],0);
      if(i+1<n)dp[i+1][j][1]=max(dp[i+1][j][1],dp[i][j][1]+1);
      if(j-1>=0)dp[i][j-1][1]=max(dp[i][j-1][1],dp[i][j][1]+1);
    }
    for(I i=n-1;i>=0;i--)for(I j=0;j<m;j++){
      if(mats[i][j]=='B')dp[i][j][2]=max(dp[i][j][2],0);
      if(i-1>=0)dp[i-1][j][2]=max(dp[i-1][j][2],dp[i][j][2]+1);
      if(j+1<m)dp[i][j+1][2]=max(dp[i][j+1][2],dp[i][j][2]+1);
    }
    for(I i=n-1;i>=0;i--)for(I j=m-1;j>=0;j--){
      if(mats[i][j]=='B')dp[i][j][3]=max(dp[i][j][3],0);
      if(i-1>=0)dp[i-1][j][3]=max(dp[i-1][j][3],dp[i][j][3]+1);
      if(j-1>=0)dp[i][j-1][3]=max(dp[i][j-1][3],dp[i][j][3]+1);
    }
    tuple<I,I,I>res={MAX,-1,-1};
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      I cur=0;
      for(I k=0;k<4;k++)cur=max(cur,dp[i][j][k]);
      res=min(res,{cur,i,j});
    }
    auto[dis,i,j]=res;
    printf("%i %i\n",i+1,j+1);
  }
}