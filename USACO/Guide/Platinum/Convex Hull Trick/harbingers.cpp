#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const Lli MAX=1e18;
const Lli MIN=-MAX;
vector<pair<I,I>>adjs[N];
pair<I,I>hars[N];
I sizs[N],pars[N],tops[N];
vector<pair<I,Lli>>stks[N];
Lli ress[N];
void dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto&adj:adjs[a]){
    auto[b,d]=adj;
    if(b==p)continue;
    dfs1(b,a);
    sizs[a]+=sizs[b];
    if(adjs[a][0].first==p||sizs[b]>sizs[adjs[a][0].first])swap(adj,adjs[a][0]);
  }
}
void dfs2(I a,I p=-1){
  pars[a]=p;
  for(auto[b,d]:adjs[a])if(b!=p){
    tops[b]=b==adjs[a][0].first?tops[a]:b;
    dfs2(b,a);
  }
}
Lli slv(pair<I,Lli>f1,pair<I,Lli>f2){
  Lli n=f2.second-f1.second,d=f1.first-f2.first;
  return d?n/d-((n^d)<0&&n%d):MIN;
}
void upd(I i,pair<I,Lli>f){
  while(stks[i].size()>1&&slv(stks[i].end()[-1],f)<=slv(stks[i].end()[-1],stks[i].end()[-2]))stks[i].pop_back();
  stks[i].push_back(f);
}
Lli qry(I i,Lli x){
  I l=0,r=stks[i].size()-1;
  while(l<r){
    I m=l+(r-l)/2;
    slv(stks[i][m],stks[i][m+1])>=x?r=m:l=m+1;
  }
  auto[m,b]=stks[i][l];
  return m*x+b;
}
Lli pat(I i,Lli x){
  Lli res=MAX;
  for(;i!=-1;i=pars[tops[i]])res=min(res,qry(tops[i],x));
  return res;
}
void dfs3(I a,I p=-1,Lli dis=0){
  if(a){
    auto[s,v]=hars[a];
    ress[a]=pat(a,v)+v*dis+s;
    upd(tops[a],{-dis,ress[a]});
  }
  reverse(adjs[a].begin(),adjs[a].end());
  for(auto[b,d]:adjs[a])if(b!=p)dfs3(b,a,dis+d);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v,d;cin>>u>>v>>d,u--,v--;
    adjs[u].push_back({v,d});
    adjs[v].push_back({u,d});
  }
  for(I i=1;i<n;i++){
    I s,v;cin>>s>>v;
    hars[i]={s,v};
  }
  upd(0,{0,0});
  for(I i=1;i<n;i++)upd(i,{0,MAX});
  dfs1(0),dfs2(0),dfs3(0);
  for(I i=1;i<n;i++)printf("%lli ",ress[i]);
}