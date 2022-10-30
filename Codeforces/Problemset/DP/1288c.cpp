#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I M=10;
const Lli MOD=1e9+7;

Lli dp[M+1][N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  dp[0][0][n-1]=1;
  for(I i=0;i<m;i++)for(I j=0;j<n;j++)for(I k=n-1;k>=0;k--){
    if(j-1>=0)(dp[i][j][k]+=dp[i][j-1][k])%=MOD;
    if(k+1<n)(dp[i][j][k]+=dp[i][j][k+1])%=MOD;
    if(j-1>=0&&k+1<n)(dp[i][j][k]-=dp[i][j-1][k+1])%=MOD;
    if(j<=k)(dp[i+1][j][k]+=dp[i][j][k])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)(res+=dp[m][i][j])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}