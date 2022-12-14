#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const Lli MOD=1e9+7;
Lli facs[2*N+1];
Lli dp1[2*N+1],dp2[2*N+1];
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
  for(I i=1;i<=2*n;i++)facs[i]=facs[i-1]*i%MOD;
  dp1[0]=1;
  for(I i=0;i<2*n;i++)(dp1[i+1]+=dp1[i]*2)%=MOD;
  for(I i=n;i<2*n;i++)(dp2[i+1]+=dp2[i]*2+bin(i,n)*2)%=MOD;
  Lli res=0;
  for(I i=0;i<=2*n;i++)(res+=dp1[i])%=MOD;
  for(I i=0;i<=2*n;i++)(res-=dp2[i])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}