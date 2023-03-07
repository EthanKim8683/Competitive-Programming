#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50000;
const I LOGN=16;
const I K=100000;
vector<I>adjs[N];
pair<I,I>pats[K];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I adds[N],rems[N];
I t=0;
I res=0;
void dfs1(I a,I p){
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  tbgs[a]=t++;
  for(auto b:adjs[a])if(b!=p)dfs1(b,a);
  teds[a]=t;
}
I dfs2(I a,I p=-1){
  I cur=adds[a];
  for(auto b:adjs[a])if(b!=p)cur+=dfs2(b,a);
  res=max(res,cur);
  return cur-rems[a];
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
I main(){
#ifndef ETHANKIM8683
  freopen("maxflow.in","r",stdin);
  freopen("maxflow.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<k;i++){
    I s,t;cin>>s>>t,s--,t--;
    pats[i]={s,t};
  }
  dfs1(0,0);
  for(I i=0;i<k;i++){
    auto[s,t]=pats[i];
    I u=lca(s,t);
    adds[s]++,adds[t]++,adds[u]--,rems[u]++;
  }
  dfs2(0);
  printf("%i\n",res);
}