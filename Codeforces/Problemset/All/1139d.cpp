#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=100000;
const Lli MOD=1e9+7;
I facs[M+1];
map<I,I>prms1;
vector<pair<I,I>>prms2;
vector<I>invs;
Lli dp[M+1];
I m;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
void trn(I p,I i=0,I val=1){
  if(i==prms2.size()){
    if(val!=p){
      Lli prb=0;
      for(I j=0;j<(1<<invs.size());j++){
        I cur=1;
        for(I k=0;k<invs.size();k++)if(j>>k&1)cur*=invs[k];
        prb+=(__builtin_popcount(j)%2?-1:1)*(m/val/cur);
      }
      (prb*=inv(m))%=MOD;
      (dp[p]+=dp[val]*prb)%=MOD;
    }
    return;
  }
  auto[prm,cnt]=prms2[i];
  invs.push_back(prm);
  for(I j=0;j<cnt;j++)trn(p,i+1,val),val*=prm;
  invs.pop_back();
  trn(p,i+1,val);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(facs,facs+M+1,0);
  for(I i=2;i*i<=M;i++)for(I j=i*i;j<=M;j+=i)facs[j]=min(facs[j],i);
  cin>>m;
  dp[1]=1;
  for(I i=2;i<=m;i++){
    prms1.clear();
    for(I j=i;j>1;j/=facs[j])prms1[facs[j]]++;
    prms2.assign(prms1.begin(),prms1.end()),trn(i);
    Lli prb=(m/i)*inv(m)%MOD;
    dp[i]=(dp[i]+1)*inv(1-prb)%MOD;
  }
  Lli res=0;
  for(I i=1;i<=m;i++)(res+=dp[i])%=MOD;
  printf("%lli\n",(res+MOD)%MOD*inv(m)%MOD);
}
/*
we can use dynamic programming, where transitions can be described
algebraically as follows:
let v = target value,
    E(x) = e.v. of x,
    D = divisors of v,
    p(x) = probability of gcd(v, [1, m]) = x
  E = E(d in D) * p(d in D) + E * p + 1
= E * (1 - p) = E(d in D) * p(d in D) + 1
= E = (E(d in D) * p(d in D) + 1) / (1 - p)
*/