#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50000;
const I LOGN=16;
const I M=50000;
const I MAX=1e9;
vector<pair<I,I>>adjs[N];
tuple<I,I,I>pats[M];
priority_queue<pair<I,I>>csts[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I deps[N];
I ress[N-1];
I pars[N];
I t=0;
void dfs1(I a,I p,I d=0){
  tbgs[a]=t++;
  deps[a]=d;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto[b,i]:adjs[a])if(b!=p){
    pars[b]=i;
    dfs1(b,a,d+1);
  }
  teds[a]=t;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
void dfs2(I a,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p){
    dfs2(b,a);
    if(csts[a].size()<csts[b].size())swap(csts[a],csts[b]);
    while(csts[b].size())csts[a].push(csts[b].top()),csts[b].pop();
  }
  if(a!=0)while(csts[a].size()){
    auto[r,d]=csts[a].top();
    if(d<deps[a]){ress[pars[a]]=-r;break;}
    csts[a].pop();
  }
}
I main(){
#ifndef ETHANKIM8683
  freopen("disrupt.in","r",stdin);
  freopen("disrupt.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I p,q;cin>>p>>q,p--,q--;
    adjs[p].push_back({q,i});
    adjs[q].push_back({p,i});
  }
  for(I i=0;i<m;i++){
    I p,q,r;cin>>p>>q>>r,p--,q--;
    pats[i]={p,q,r};
  }
  dfs1(0,0);
  for(I i=0;i<m;i++){
    auto[p,q,r]=pats[i];
    I d=deps[lca(p,q)];
    csts[p].push({-r,d}),csts[q].push({-r,d});
  }
  fill_n(ress,n-1,-1);
  dfs2(0);
  for(I i=0;i<n-1;i++)printf("%i\n",ress[i]);
}