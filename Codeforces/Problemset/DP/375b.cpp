#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=5000;
const I M=5000;

C cels[N][M+1];
I dp[M][M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++){
      if(cels[i][j]!='1')continue;
      I k=j;
      while(j<m&&cels[i][j]=='1')j++;
      dp[k][j-1]++;
    }
  }
  for(I i=m-1;i>=0;i--){
    for(I j=0;j+i<m;j++){
      if(j-1>=0)dp[j][j+i]+=dp[j-1][j+i];
      if(j+i+1<m)dp[j][j+i]+=dp[j][j+i+1];
      if(j-1>=0&&j+i+1<m)dp[j][j+i]-=dp[j-1][j+i+1];
    }
  }
  I res=0;
  for(I i=0;i<m;i++)for(I j=i;j<m;j++)res=max(res,dp[i][j]*(j-i+1));
  printf("%i\n",res);
}