#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=30;
const I K=5000;
const Lli MOD=1e9+7;
vector<pair<I,I>>prms;
I bits[N+1];
Lli dp[K];
Lli facs[N+1];
Lli mpw(Lli x,I y){
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
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I x,y;cin>>x>>y;
  if(y%x)printf("0"),exit(0);
  I fac=y/x;
  for(I i=2;i*i<=fac;i++){
    I cnt=0;
    while(fac%i==0)cnt++,fac/=i;
    if(cnt)prms.push_back({i,cnt});
  }
  if(fac>1)prms.push_back({fac,1});
  bits[0]=1;
  for(I i=0;i<prms.size();i++){
    auto[prm,cnt]=prms[i];
    bits[i+1]=bits[i]*(cnt+1);
  }
  dp[bits[prms.size()]-1]=y/x;
  for(I i=bits[prms.size()]-1;i>0;i--)for(I j=0;j<prms.size();j++){
    auto[prm,tot]=prms[j];
    if(i/bits[j]%(tot+1)==0)continue;
    dp[i-bits[j]]=dp[i]/prm;
  }
  for(I i=0;i<bits[prms.size()];i++)dp[i]=mpw(2,dp[i]-1);
  for(I i=0;i<bits[prms.size()];i++)for(I j=0;j<i;j++){
    B vld=1;
    for(I k=0;k<prms.size();k++){
      auto[prm,tot]=prms[k];
      vld&=j/bits[k]%(tot+1)<=i/bits[k]%(tot+1);
    }
    if(vld)(dp[i]-=dp[j])%=MOD;
  }
  printf("%lli\n",(dp[bits[prms.size()]-1]+MOD)%MOD);
}