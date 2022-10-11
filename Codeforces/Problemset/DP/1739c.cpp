#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=60;
const Lli MOD=998244353;

Lli dp[N/2+1][N/2+1][3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    I m=n/2;
    for(I i=0;i<=m;i++)for(I j=0;j<=m;j++)for(I k=0;k<3;k++)dp[i][j][k]=0;
    dp[0][0][2]=1;
    for(I i=0;i<=m;i++)for(I j=0;j<=m;j++)for(I k=0;k<3;k++){
      I t=(i+j)%4;
      if(t==0||t==3){
        if(i+1<=m)(dp[i+1][j][k==2?0:k]+=dp[i][j][k])%=MOD;
        if(j+1<=m)(dp[i][j+1][k]+=dp[i][j][k])%=MOD;
      }
      if(t==1||t==2){
        if(i+1<=m)(dp[i+1][j][k]+=dp[i][j][k])%=MOD;
        if(j+1<=m)(dp[i][j+1][k==2?1:k]+=dp[i][j][k])%=MOD;
      }
    }
    printf("%lli %lli %lli\n",dp[m][m][0],dp[m][m][1],dp[m][m][2]);
  }
}