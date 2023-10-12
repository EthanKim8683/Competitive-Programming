#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I LOGD=50;
const Lli MOD=998244353;
vector<Lli>prms;
Lli facs[LOGD+1];
Lli invs[LOGD+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=LOGD;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=LOGD;i++)invs[i]=inv(facs[i]);
  Lli d;cin>>d;
  for(Lli i=2;i*i<=d;i++)if(d%i==0){
    prms.push_back(i);
    for(;d%i==0;d/=i);
  }
  if(d>1)prms.push_back(d);
  I q;cin>>q;
  while(q--){
    Lli u,v;cin>>u>>v;
    Lli g=gcd(u,v),x=u/g,y=v/g;
    Lli res=1,tot=0;
    for(auto i:prms){
      I cnt=0;
      for(;x%i==0;x/=i)cnt++;
      (res*=invs[cnt])%=MOD,tot+=cnt;
    }
    (res*=facs[tot])%=MOD;
    tot=0;
    for(auto i:prms){
      I cnt=0;
      for(;y%i==0;y/=i)cnt++;
      (res*=invs[cnt])%=MOD,tot+=cnt;
    }
    (res*=facs[tot])%=MOD;
    printf("%lli\n",res);
  }
}