#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
const Lli MOD=1e9+7;
Lli facs[N+1];
B dp[9*N+1];
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
  I a,b,n;cin>>a>>b>>n;
  dp[0]=1;
  for(I i=0;i<=9*n;i++){
    if(i*10+a<=9*n)dp[i*10+a]|=dp[i];
    if(i*10+b<=9*n)dp[i*10+b]|=dp[i];
  }
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  Lli res=0;
  for(I i=0;i<=n;i++)if(dp[i*a+(n-i)*b])(res+=bin(n,i))%=MOD;
  printf("%lli\n",res);
}