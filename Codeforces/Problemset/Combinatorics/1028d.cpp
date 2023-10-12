#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
using B=bool;
const I N=363304;
const I LOGN=19;
const Lli MOD=1e9+7;
const I MAX=1e9;
const I MIN=-MAX;
map<I,pair<I,I>>rngs1;
vector<pair<I,pair<I,I>>>rngs2;
I spas[2][N+1][LOGN];
B ress[N][2];
I n;
void bld(){
  for(I i=0;i<2;i++)for(I j=1;j<LOGN;j++)for(I k=0;k+(1<<j)<=n+1;k++)spas[i][k][j]=min(spas[i][k][j-1],spas[i][k+(1<<(j-1))][j-1]);
}
I qry(I t,I l,I r){
  I d=31-__builtin_clz(r-l);
  return min(spas[t][l][d],spas[t][r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&spas[0][0][0],&spas[0][0][0]+2*(N+1)*LOGN,MAX);
  cin>>n;
  for(I i=0;i<n;i++){
    S s;I p;cin>>s>>p;
    if(s=="ADD")rngs1[p]={i,n};
    if(s=="ACCEPT")rngs1[p].second=i;
  }
  rngs2.assign(rngs1.begin(),rngs1.end());
  for(auto[p,rng]:rngs2){
    auto[l,r]=rng;
    spas[0][r][0]=p,spas[1][r][0]=-p;
  }
  bld();
  for(I i=0;i<rngs2.size();i++){
    auto[p,rng]=rngs2[i];
    auto[l,r]=rng;
    if(qry(0,l,r)<p)ress[i][0]=1;
    if(-qry(1,l,r)>p)ress[i][1]=1;
  }
  I low=MIN,upp=MAX;
  for(I i=0;i<rngs2.size();i++){
    auto[p,rng]=rngs2[i];
    auto[l,r]=rng;
    if(r!=n)continue;
    if(ress[i][0])upp=min(upp,p);
    if(ress[i][1])low=max(low,p);
  }
  Lli res=1;
  for(I i=0;i<rngs2.size();i++){
    auto[p,rng]=rngs2[i];
    auto[l,r]=rng;
    if(r!=n)continue;
    if(ress[i][0]||ress[i][1])continue;
    res+=low<p&&p<=upp;
  }
  if(upp<=low)res=0;
  for(I i=0;i<rngs2.size();i++){
    auto[p,rng]=rngs2[i];
    auto[l,r]=rng;
    if(r==n)continue;
    (res*=2-ress[i][0]-ress[i][1])%=MOD;
  }
  printf("%lli\n",res);
}
/*
denote add[p] the index of the action when p was added and acc[p] the index of
the action when p was accepted

two orders are "coinciding" if add[p] < add[q] < acc[p] or add[p] < acc[q] <
acc[p]

if p and q coincide, acc[p] < acc[q] and p > q, p and q can either both be buy
or p is sell and q is buy

if p and q coincide, acc[p] < acc[q] and p < q, p and q can either both be sell
or p is buy and q is sell
'
meanwhile, for all p such that acc[p] does not exist, we can choose at most
one p to be the best possible sell offer, provided no confirmed buy or sell
offers are violated
*/