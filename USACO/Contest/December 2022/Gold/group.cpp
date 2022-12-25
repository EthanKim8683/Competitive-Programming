#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
set<I>adjs[N];
vector<tuple<I,I,Lli>>edgs;
priority_queue<pair<I,I>>ques;
I pars[N];
Lli segs[2*N];
I n;
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]<pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I siz(I i){
  return-pars[fnd(i)];
}
void upd(I i,Lli val){
  for(segs[i+=n]=val;i>1;i>>=1)segs[i>>1]=min(segs[i],segs[i^1]);
}
Lli qry(I l,I r){
  Lli res=MAX;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=min(res,segs[l++]);
    if(r&1)res=min(res,segs[--r]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  fill_n(segs,2*N,MAX);
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].insert(v);
    adjs[v].insert(u);
  }
  for(I i=0;i<n;i++)upd(i,adjs[i].size());
  for(I i=0;i<n;i++)ques.push({-adjs[i].size(),i});
  while(ques.size()){
    auto[siz,a]=ques.top();ques.pop();
    if((siz*=-1)!=adjs[a].size())continue;
    Lli cur=qry(0,n);
    for(auto b:adjs[a]){
      adjs[b].erase(a);
      upd(b,adjs[b].size());
      edgs.push_back({a,b,cur});
      ques.push({-adjs[b].size(),b});
    }
    upd(a,MAX);
    adjs[a].clear();
  }
  reverse(edgs.begin(),edgs.end());
  Lli res=0;
  for(auto[a,b,cur]:edgs){
    uni(a,b);
    res=max(res,siz(a)*cur);
  }
  printf("%lli\n",res);
}