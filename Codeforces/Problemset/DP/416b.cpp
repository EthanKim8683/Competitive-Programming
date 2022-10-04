#include<bits/stdc++.h>

using namespace std;

using I=int;

const I M=50000;
const I N=5;

I dp[M][N];
I tims[M][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,n;cin>>m>>n;
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)cin>>tims[i][j];
  for(I i=0;i<m;i++)for(I j=0;j<n;j++){
    I cur=0;
    if(i-1>=0)cur=max(cur,dp[i-1][j]);
    if(j-1>=0)cur=max(cur,dp[i][j-1]);
    dp[i][j]=cur+tims[i][j];
  }
  for(I i=0;i<m;i++)printf("%i ",dp[i][n-1]);
}