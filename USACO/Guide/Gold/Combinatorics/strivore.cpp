#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
const I K=1e6;
const I N=1e6;
const Lli MOD=1e9+7;
Lli facs[K+N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  I k;cin>>k;
  S s;cin>>s;
  I n=s.size();
  facs[0]=1;
  for(I i=1;i<=k+n;i++)facs[i]=facs[i-1]*i%MOD;
  Lli res=0;
  for(I i=0;i<=k;i++)(res+=mpw(25,k-i)*mpw(26,i)%MOD*bin((n-1)+(k-i),n-1))%=MOD;
  printf("%lli\n",res);
}