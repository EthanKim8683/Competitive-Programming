#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=5e5;
const I M=5e5;
const I W=5e5;
const I Q=5e5;
tuple<I,I,I>edgs[M];
vector<I>inds[W+1];
set<I>chks[W+1];
multimap<I,I>qrys[Q];
I pars[N];
vector<pair<I,I>>adjs[N];
I viss[N];
vector<I>curs;
B ress[Q];
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
B dfs(I a,I i=-1){
  if(viss[a])return viss[a]==1;
  viss[a]=1;
  for(auto[b,j]:adjs[a])if(i!=j&&dfs(b,j))return 1;
  viss[a]=2;
  return 0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    edgs[i]={w,u,v};
    inds[w].push_back(i);
  }
  I q;cin>>q;
  for(I i=0;i<q;i++){
    I k;cin>>k;
    for(I j=0;j<k;j++){
      I l;cin>>l,l--;
      auto[w,u,v]=edgs[l];
      qrys[i].insert({w,l});
      chks[w].insert(i);
    }
  }
  fill_n(pars,n,-1);
  fill_n(ress,q,1);
  for(I i=1;i<=W;i++){
    for(auto j:chks[i]){
      auto[low,upp]=qrys[j].equal_range(i);
      for(auto it=low;it!=upp;it++){
        I k=it->second;
        auto[w,u,v]=edgs[k];
        u=fnd(u),v=fnd(v);
        ress[j]&=u!=v;
        adjs[u].push_back({v,k});
        adjs[v].push_back({u,k});
        curs.push_back(u);
        curs.push_back(v);
      }
      for(auto k:curs)ress[j]&=!dfs(k);
      for(auto it=low;it!=upp;it++){
        I k=it->second;
        auto[w,u,v]=edgs[k];
        u=fnd(u),v=fnd(v);
        adjs[u].clear();
        adjs[v].clear();
        viss[u]=viss[v]=0;
      }
      curs.clear();
    }
    for(auto j:inds[i]){
      auto[w,u,v]=edgs[j];
      uni(u,v);
    }
  }
  for(I i=0;i<q;i++)printf("%s\n",ress[i]?"YES":"NO");
}
/*
since an edge can only replace another edge with the same weight in an MST, we
can process the edges in increasing order of weight constructing the MST and
answering queries as we go

since the same nodes will be connected after each set of edges with equal
weight, regardless of which subset of edges are chosen, each weight is
independent

if any subset of edges in a query forms a cycle, the answer is "NO", since
a tree cannot have cycles

if it is impossible to include any of the edges in a query as a result of
edges with lesser weight, the answer is also "NO"
*/