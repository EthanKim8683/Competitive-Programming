#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=4000;
const Lli MOD=1e9+7;
Lli facs[N+1];
Lli bins[N+1];
Lli dp[N][N];
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
  I n;cin>>n;
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=n-1;i++)bins[i]=bin(n,i);
  dp[0][0]=1;
  for(I i=0;i<n-1;i++)for(I j=0;j<=i;j++){
    (dp[i+1][j+1]+=dp[i][j])%=MOD;
    (dp[i+1][j]+=j*dp[i][j])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<=n-1;i++)for(I j=0;j<=i;j++)(res+=dp[i][j]*bins[i])%=MOD;
  printf("%lli\n",res);
}