#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=2e5;
const I MAX=1e9;

C plys[N+1];
I dp[N][2][2][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>plys;
    I res=MAX;
    for(I o=0;o<3;o++){
      for(I i=0;i<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)for(I l=0;l<2;l++)dp[i][j][k][l]=MAX;
      C ply=plys[(0+o)%n];
      dp[0][0][0][0]=ply!='L';
      dp[0][1][1][0]=ply!='R';
      for(I i=0;i+1<n;i++)for(I j=0;j<2;j++){
        C ply=plys[(i+1+o)%n];
        dp[i+1][j][1][0]=min(dp[i+1][j][1][0],dp[i][j][0][0]+(ply!='R'));
        dp[i+1][j][0][0]=min(dp[i+1][j][0][0],dp[i][j][1][0]+(ply!='L'));
        dp[i+1][j][1][0]=min(dp[i+1][j][1][0],dp[i][j][0][1]+(ply!='R'));
        dp[i+1][j][0][0]=min(dp[i+1][j][0][0],dp[i][j][1][1]+(ply!='L'));
        dp[i+1][j][1][1]=min(dp[i+1][j][1][1],dp[i][j][1][0]+(ply!='R'));
        dp[i+1][j][0][1]=min(dp[i+1][j][0][1],dp[i][j][0][0]+(ply!='L'));
      }
      res=min(res,dp[n-1][0][1][0]);
      res=min(res,dp[n-1][1][0][0]);
      res=min(res,dp[n-1][0][1][1]);
      res=min(res,dp[n-1][1][0][1]);
    }
    printf("%i\n",res);
  }
}