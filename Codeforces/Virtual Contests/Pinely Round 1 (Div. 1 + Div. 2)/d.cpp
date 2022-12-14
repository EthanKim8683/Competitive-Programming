#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli MOD=1e9+7;
const I N=1e6;
const I K=1e6;
Lli facs[N+K+1];
Lli pows[N+K+1];
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
  I n,k;cin>>n>>k;
  pows[0]=1;
  for(I i=1;i<=n+k;i++)pows[i]=pows[i-1]*3%MOD;
  facs[0]=1;
  for(I i=1;i<=n+k;i++)facs[i]=facs[i-1]*i%MOD;
  if(k==0)printf("%lli\n",pows[n]),exit(0);
  Lli res=0;
  for(I i=0;i<=k-1&&n-(k+i)>=0;i++){
    Lli x=bin(k-1,i)*pows[k-1-i]%MOD,y=x;
    (x*=bin(n-(k+i)+i,i))%=MOD;
    (x*=pows[n-(k+i)])%=MOD;
    (res+=x)%=MOD;
    if(n-(k+i)>0){
      (y*=bin(n-(k+i)-1+i+1,i+1))%=MOD;
      (y*=pows[n-(k+i)-1])%=MOD;
      (res+=y)%=MOD;
    }
  }
  printf("%lli\n",res);
}