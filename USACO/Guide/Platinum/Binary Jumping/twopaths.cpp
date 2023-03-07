#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=3e5;
const I LOGN=19;
I a_arr[N];
vector<pair<I,I>>adjs[N];
Lli vtxs[N],edgs[N];
map<I,Lli>excs[N];
Lli sums[N];
I ancs[N][LOGN];
Lli adds[N],subs[N];
I tbgs[N],teds[N];
I t=0;
void dfs1(I a,I p,Lli v,Lli e){
  tbgs[a]=t++;
  vtxs[a]=v,edgs[a]=e;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto[b,w]:adjs[a])if(b!=p)dfs1(b,a,v+a_arr[b],e+w);
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
Lli dfs2(I a,I p=-1){
  for(auto[b,w]:adjs[a])if(b!=p){
    Lli cur=max(dfs2(b,a)+a_arr[b]-2*w,0ll);
    sums[a]+=cur,excs[a][b]=cur;
  }
  return sums[a];
}
void dfs3(I a,I p=-1){
  for(auto[b,w]:adjs[a])if(b!=p){
    Lli cur=max(sums[a]-excs[a][b]+a_arr[a]-2*w,0ll);
    sums[b]+=cur,excs[b][a]=cur;
    dfs3(b,a);
  }
}
void dfs4(I a,I p=-1){
  for(auto[b,w]:adjs[a])if(b!=p){
    adds[b]+=adds[a],subs[b]+=subs[a];
    dfs4(b,a);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs[u].push_back({v,w});
    adjs[v].push_back({u,w});
  }
  dfs1(0,0,a_arr[0],0),dfs2(0),dfs3(0);
  for(I i=1;i<n;i++){
    I j=ancs[i][0];
    adds[i]=sums[i];
    subs[i]=excs[i][j]+excs[j][i];
  }
  dfs4(0);
  while(q--){
    I u,v;cin>>u>>v,u--,v--;
    I t=lca(u,v);
    Lli res=0;
    res+=vtxs[u]+vtxs[v]-2*vtxs[t]+a_arr[t];
    res-=edgs[u]+edgs[v]-2*edgs[t];
    res+=adds[u]+adds[v]-2*adds[t]+sums[t];
    res-=subs[u]+subs[v]-2*subs[t];
    printf("%lli\n",res);
  }
}