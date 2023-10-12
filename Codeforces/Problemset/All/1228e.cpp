#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=250;
const Lli MOD=1e9+7;
Lli facs[N+1];
Lli dp[N+1][N+1];
Lli bins[N+1][N+1],mpws1[N+1],mpws2[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  for(I i=0;i<=n;i++)for(I j=0;j<=i;j++)bins[i][j]=bin(i,j);
  for(I i=0;i<=n;i++)mpws1[i]=mpw(k-1,i),mpws2[i]=mpw(k,i);
  dp[0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=n;j++){
    for(I l=1;l<=j;l++)(dp[i+1][j]+=dp[i][j]*bins[j][l]%MOD*mpws1[n-l]%MOD)%=MOD;
    for(I l=1;l<=n-j;l++)(dp[i+1][j+l]+=dp[i][j]*bins[n-j][l]%MOD*mpws2[j]%MOD*mpws1[n-j-l]%MOD)%=MOD;
  }
  printf("%lli\n",dp[n][n]);
}
/*
dynamic programming can be used, processing each row, keeping track of the
number of columns without a 1
*/