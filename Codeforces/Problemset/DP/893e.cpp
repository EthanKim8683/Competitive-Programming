#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I X=1e6;
const I Y=1e6;
const I P=7;
const Lli MOD=1e9+7;
I eras[X+1];
vector<I>cnts;
Lli facs[2*Y+1];
Lli pows[Y+1];
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
  iota(eras,eras+X+1,0);
  for(I i=2;i*i<=X;i++)if(eras[i]==i)for(I j=i*i;j<=X;j+=i)if(eras[j]==j)eras[j]=i;
  facs[0]=1;
  for(I i=1;i<=2*Y;i++)facs[i]=facs[i-1]*i%MOD;
  pows[0]=1;
  for(I i=1;i<=Y;i++)pows[i]=pows[i-1]*2%MOD;
  I q;cin>>q;
  while(q--){
    I x,y;cin>>x>>y;
    cnts.clear();
    if(x!=1){
      I pre=eras[x],cnt=1,j=0;
      for(I i=x/pre;i!=1;i/=pre){
        if(eras[i]!=pre){
          cnts.push_back(cnt);
          pre=eras[i],cnt=0;
        }
        cnt++;
      }
      cnts.push_back(cnt);
    }
    Lli res=pows[y-1];
    for(auto cnt:cnts)(res*=bin(y-1+cnt,y-1))%=MOD;
    printf("%lli\n",res);
  }
}