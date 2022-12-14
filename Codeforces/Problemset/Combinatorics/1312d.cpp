#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=2e5;
const Lli MOD=998244353;
Lli facs[M+1];
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
  I n,m;cin>>n>>m;
  facs[0]=1;
  for(I i=1;i<=m;i++)facs[i]=facs[i-1]*i%MOD;
  Lli res=0;
  for(I i=1;i<n-1;i++){
    Lli cur=1;
    (cur*=bin(m,n-1))%=MOD;
    (cur*=bin(n-2,i))%=MOD;
    (cur*=i)%=MOD;
    (res+=cur)%=MOD;
  }
  printf("%lli\n",res);
}