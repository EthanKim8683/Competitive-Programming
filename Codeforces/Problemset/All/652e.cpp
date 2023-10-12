#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I M=3e5;
pair<I,I>edgs[M];
vector<pair<I,I>>adjs1[N],adjs2[N];
B arts[M];
I lows[N];
B viss[N];
B bdgs[M];
I pars[N];
vector<I>stks;
B vlds[M];
I a,b;
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
void dfs1(I x,I p=-1){
  if(viss[x])return;
  viss[x]=1;
  I mid=lows[x]=t++;
  for(auto[y,i]:adjs1[x])if(i!=p){
    dfs1(y,i);
    lows[x]=min(lows[x],lows[y]);
    bdgs[i]=lows[y]>mid;
  }
}
void dfs2(I x,I p=-1){
  if(b==x){
    for(auto i:stks)vlds[i]=1;
    return;
  }
  for(auto[y,i]:adjs2[x])if(y!=p){
    stks.push_back(i);
    dfs2(y,x);
    stks.pop_back();
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I x,y,z;cin>>x>>y>>z,x--,y--;
    adjs1[x].push_back({y,i});
    adjs1[y].push_back({x,i});
    edgs[i]={x,y};
    arts[i]=z;
  }
  cin>>a>>b,a--,b--;
  dfs1(0);
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    auto[x,y]=edgs[i];
    if(bdgs[i])continue;
    uni(x,y);
  }
  a=fnd(a),b=fnd(b);
  for(I i=0;i<m;i++){
    auto[x,y]=edgs[i];
    if(!bdgs[i])continue;
    x=fnd(x),y=fnd(y);
    adjs2[x].push_back({y,i});
    adjs2[y].push_back({x,i});
  }
  dfs2(a);
  for(I i=0;i<m;i++){
    auto[x,y]=edgs[i];
    if(!vlds[i])continue;
    uni(x,y);
  }
  a=fnd(a),b=fnd(b);
  for(I i=0;i<m;i++){
    auto[x,y]=edgs[i];
    if(bdgs[i])continue;
    x=fnd(x),y=fnd(y);
    vlds[i]=a==x||a==y||b==x||b==y;
  }
  B res=0;
  for(I i=0;i<m;i++)res|=vlds[i]&&arts[i];
  printf("%s\n",res?"YES":"NO");
}
/*
if an edge is a bridge, we can remove it if it doesn't connect Johnny to the
artifact-dealer

if there are any remaining artifact-containing edges connected to Johnny and
the artifact dealer, Johnny can find an artifact and sell it to the dealer

this is because at no point will Johnny be forced to use the same edge to
reach an artifact and to get to the dealer since all such edges are removed
*/