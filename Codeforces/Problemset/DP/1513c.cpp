#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I M=2e5;
const Lli MOD=1e9+7;

Lli dp[10][M+1][10];
Lli sums[10][M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=0;i<10;i++){
    dp[i][0][i]=1;
    for(I j=0;j<M;j++){
      for(I k=0;k<9;k++)(dp[i][j+1][k+1]+=dp[i][j][k])%=MOD;
      (dp[i][j+1][0]+=dp[i][j][9])%=MOD;
      (dp[i][j+1][1]+=dp[i][j][9])%=MOD;
    }
    for(I j=0;j<=M;j++)for(I k=0;k<10;k++)
      (sums[i][j]+=dp[i][j][k])%=MOD;
  }
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    Lli res=0;
    for(;n;n/=10)(res+=sums[n%10][m])%=MOD;
    printf("%lli\n",res);
  }
}