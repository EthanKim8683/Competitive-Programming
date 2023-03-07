#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MOD=998244353;
const I N=5e5;
Lli facs[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<k)return 0;
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  Lli res=0;
  for(I i=1;i<=n;i++)(res+=bin(n/i-1,k-1))%=MOD;
  printf("%lli\n",res);
}