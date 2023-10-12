#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using C=char;
const I N=1e5;
const I M=1e5;
const I W=1e6;
pair<I,I>edgs[M];
vector<I>bucs[W+1];
vector<pair<I,I>>adjs[N];
set<I>curs;
I pars[N];
I ress[M];
I lows[N];
B viss[N];
I t=0;
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
void dfs(I a,I j=-1){
  if(viss[a])return;
  viss[a]=1;
  I tim=lows[a]=t++;
  for(auto[b,i]:adjs[a])if(i!=j){
    dfs(b,i);
    if(lows[b]>tim)ress[i]=0;
    lows[a]=min(lows[a],lows[b]);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b,w;cin>>a>>b>>w,a--,b--;
    edgs[i]={a,b};
    bucs[w].push_back(i);
  }
  fill_n(ress,m,1);
  fill_n(pars,n,-1);
  for(I i=1;i<=W;i++){
    curs.clear();
    for(auto j:bucs[i]){
      auto[a,b]=edgs[j];
      a=fnd(a),b=fnd(b);
      if(a==b){
        ress[j]=2;
      }else{
        curs.insert(a);
        curs.insert(b);
        adjs[a].push_back({b,j});
        adjs[b].push_back({a,j});
      }
    }
    for(auto a:curs)if(!viss[a])dfs(a);
    for(auto a:curs)viss[a]=0,adjs[a].clear();
    for(auto j:bucs[i]){
      auto[a,b]=edgs[j];
      uni(a,b);
    }
  }
  for(I i=0;i<m;i++)printf("%s\n",(C*[]){"any","at least one","none"}[ress[i]]);
}
/*
we can process all edges with the same weight at the same time, since only
edges with the same weight can determine whether an edge is "any" or "at least
one"

using Kruskal's, we can look at the components the edges connect

if an edge connects a component with itself, its result is "none"

for all remaining edges, we can form a graph, on which we will look for
bridges, as those edges result in "any"

otherwise, the edge results in "at least one"
*/