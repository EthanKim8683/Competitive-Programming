#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=400000;
const I M=400000;
const I MAX=1e9;
pair<I,I>edgs[M];
vector<pair<I,I>>adjs[N];
B viss[N];
I lows[N];
B bdgs[N];
I pars[N];
pair<I,I>dirs[M];
I t=0;
void dfs1(I a,I i=-1){
  if(viss[a])return;
  viss[a]=1;
  I tim=lows[a]=t++;
  for(auto[b,j]:adjs[a])if(j!=i){
    dfs1(b,j);
    lows[a]=min(lows[a],lows[b]);
    if(lows[b]>tim)bdgs[j]=1;
  }
}
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I siz(I i){
  return-pars[fnd(i)];
}
void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto[b,i]:adjs[a]){
    if(dirs[i]==pair<I,I>{-1,-1})dirs[i]={b,a};
    dfs2(b);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    edgs[i]={u,v};
    adjs[u].push_back({v,i});
    adjs[v].push_back({u,i});
  }
  dfs1(0);
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++)if(!bdgs[i]){
    auto[u,v]=edgs[i];
    uni(u,v);
  }
  pair<I,I>snk={0,-1};
  for(I i=0;i<n;i++)snk=max(snk,{siz(i),i});
  auto[res,a]=snk;
  fill_n(dirs,m,pair<I,I>{-1,-1});
  fill_n(viss,n,0);
  dfs2(a);
  printf("%i\n",res);
  for(I i=0;i<m;i++){
    auto[u,v]=dirs[i];
    printf("%i %i\n",u+1,v+1);
  }
}
/*
by turning all cycles into directed cycles, any city on a cycle can visit any
other city on the same cycle

treating all cycles as nodes and all bridges as edges between those nodes, we
now have a tree

since trees don't have cycles, one node in this tree must not be able to visit
any other node

by setting this node to the maximum cycle and having all other nodes direct
towards this node, we can ensure the minimum r[i] is equal to the size of the
cycle, as all other nodes will visit at least said cycle
*/