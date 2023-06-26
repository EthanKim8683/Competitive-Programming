#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I K=N*N;
const Lli MOD=1e9+7;
Lli dp[N+1][K+1];
Lli facs[N+1],bins[N+1];
Lli mpws[N][N+1];
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
  I n;Lli m;I k;cin>>n>>m>>k;
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=n;i++)bins[i]=bin(n,i);
  for(I i=0;i<n;i++)for(I j=0;j<=n;j++)mpws[i][j]=mpw(bins[j],1+(m-1-i)/n);
  dp[0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++)for(I l=0;l<=n&&j+l<=k;l++)(dp[i+1][j+l]+=dp[i][j]*mpws[i][l])%=MOD;
  printf("%lli\n",dp[n][k]);
}