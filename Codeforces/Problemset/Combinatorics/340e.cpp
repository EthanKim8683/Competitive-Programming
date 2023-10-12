#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const Lli MOD=1e9+7;
Lli facs[N+1];
I prms[N+1];
I cnts[N+1];
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
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  for(I i=1;i<=n;i++)cin>>prms[i];
  for(I i=1;i<=n;i++){
    I j=prms[i];
    if(j==-1)continue;
    cnts[i]++,cnts[j]++;
  }
  I two=0,one=0;
  for(I i=1;i<=n;i++)two+=cnts[i]==2,one+=cnts[i]==1;
  Lli res=0;
  for(I i=0;i<=n-two-one;i++)(res+=(i%2==0?1:-1)*bin(n-two-one,i)*facs[n-two-one/2-i])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
we can use the principle of inclusion-exclusion to exclude the number of
permutations with one or more fixed points, similar to one of the possible
solutions for "Montmort Number" on Yosupo
*/