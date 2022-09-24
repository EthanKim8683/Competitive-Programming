#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using Lli=long long int;

const I N=100;
const I M=1000;
const Lli MAX=1e18;

C cels[N][M+1];
Lli dp[N][M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m,x,y;cin>>n>>m>>x>>y;
    for(I i=0;i<n;i++)for(I j=0;j<=m;j++)dp[i][j]=MAX;
    for(I i=0;i<n;i++)cin>>cels[i];
    Lli res=0;
    for(I i=0;i<n;i++){
      dp[i][0]=0;
      for(I j=0;j<m;j++){
        if(cels[i][j]=='.'){
          dp[i][j+1]=min(dp[i][j+1],dp[i][j]+x);
          if(j+1<m&&cels[i][j+1]=='.')dp[i][j+2]=min(dp[i][j+2],dp[i][j]+y);
        }else dp[i][j+1]=min(dp[i][j+1],dp[i][j]);
      }
      res+=dp[i][m];
    }
    printf("%lli\n",res);
  }
}