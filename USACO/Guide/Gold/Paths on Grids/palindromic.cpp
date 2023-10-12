#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=500;
const Lli MOD=1e9+7;
C frms[N][N+1];
Lli dp[2][N][N];
I main(){
#ifndef ETHANKIM8683
  freopen("palpath.in","r",stdin);
  freopen("palpath.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>frms[i];
  dp[0][0][0]=1;
  for(I i=0;i<n-1;i++)for(I j=0;j<=i;j++)for(I k=0;k<=i;k++){
    if(frms[i-j][j]==frms[n-1-(i-k)][n-1-k]){
      if(i+1<n-1||j==n-1-k)(dp[(i+1)%2][j][k]+=dp[i%2][j][k])%=MOD;
      if(i+1<n-1||j+1==n-1-k)(dp[(i+1)%2][j+1][k]+=dp[i%2][j][k])%=MOD;
      if(i+1<n-1||j==n-1-(k+1))(dp[(i+1)%2][j][k+1]+=dp[i%2][j][k])%=MOD;
      if(i+1<n-1||j+1==n-1-(k+1))(dp[(i+1)%2][j+1][k+1]+=dp[i%2][j][k])%=MOD;
    }
    dp[i%2][j][k]=0;
  }
  Lli res=0;
  for(I i=0;i<n;i++)(res+=dp[(n-1)%2][i][n-1-i])%=MOD;
  printf("%lli\n",res);
}