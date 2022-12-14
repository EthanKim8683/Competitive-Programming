#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I A=5000;
const I B=5000;
const I C=5000;
const Lli MOD=998244353;
Lli facs[A+1];
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
Lli pmp(I a,I b){
  Lli res=1;
  for(I i=1;i<=min(a,b);i++){
    Lli cur=1;
    (cur*=bin(a,i))%=MOD;
    (cur*=bin(b,i))%=MOD;
    (cur*=facs[i])%=MOD;
    (res+=cur)%=MOD;
  }
  return res;
}
I main(){
  facs[0]=1;
  for(I i=1;i<=A;i++)facs[i]=facs[i-1]*i%MOD;
  I a,b,c;cin>>a>>b>>c;
  Lli res=1;
  (res*=pmp(a,b))%=MOD;
  (res*=pmp(b,c))%=MOD;
  (res*=pmp(c,a))%=MOD;
  cout<<res<<endl;
}