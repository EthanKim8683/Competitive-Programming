#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I K=2*N;
const Lli MOD=998244353;

Lli dp[N][K+1][4];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  dp[0][1][0b00]=dp[0][1][0b11]=1;
  dp[0][2][0b01]=dp[0][2][0b10]=1;
  for(I i=0;i+1<n;i++)for(I j=0;j<=k;j++){
    if(j+0<=k)(dp[i+1][j+0][0b00]+=dp[i][j][0b00])%=MOD;
    if(j+1<=k)(dp[i+1][j+1][0b01]+=dp[i][j][0b00])%=MOD;
    if(j+1<=k)(dp[i+1][j+1][0b10]+=dp[i][j][0b00])%=MOD;
    if(j+1<=k)(dp[i+1][j+1][0b11]+=dp[i][j][0b00])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b00]+=dp[i][j][0b01])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b01]+=dp[i][j][0b01])%=MOD;
    if(j+2<=k)(dp[i+1][j+2][0b10]+=dp[i][j][0b01])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b11]+=dp[i][j][0b01])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b00]+=dp[i][j][0b10])%=MOD;
    if(j+2<=k)(dp[i+1][j+2][0b01]+=dp[i][j][0b10])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b10]+=dp[i][j][0b10])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b11]+=dp[i][j][0b10])%=MOD;
    if(j+1<=k)(dp[i+1][j+1][0b00]+=dp[i][j][0b11])%=MOD;
    if(j+1<=k)(dp[i+1][j+1][0b01]+=dp[i][j][0b11])%=MOD;
    if(j+1<=k)(dp[i+1][j+1][0b10]+=dp[i][j][0b11])%=MOD;
    if(j+0<=k)(dp[i+1][j+0][0b11]+=dp[i][j][0b11])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<4;i++)(res+=dp[n-1][k][i])%=MOD;
  printf("%i\n",res);
}