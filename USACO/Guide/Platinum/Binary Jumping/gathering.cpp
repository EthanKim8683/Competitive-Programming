#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
vector<I>adjs[N];
vector<I>incs[N];
I viss[N];
I tbgs[N],teds[N];
I ancs[N][LOGN];
B ress[N];
I t=0;
B dfs1(I a){
  if(viss[a]==1)return 1;
  if(viss[a]==2)return 0;
  viss[a]=1;
  for(auto b:incs[a])if(dfs1(b))return 1;
  viss[a]=2;
  return 0;
}
void dfs2(I a,I p){
  tbgs[a]=t++;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(b!=p)dfs2(b,a);
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
I bef(I a,I b){
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return a;
}
void dfs3(I a,I p){
  if(!ress[a])return;
  ress[a]=0;
  for(auto b:adjs[a])if(b!=p)dfs3(b,a);
}
void dfs4(I a,I p){
  if(viss[a]==3)return;
  viss[a]=3;
  for(auto b:incs[a]){
    I c=lca(a,b);
    if(c!=a)dfs3(a,p);
    if(c==a)dfs3(a,bef(b,a));
  }
  for(auto b:adjs[a])if(b!=p)dfs4(b,a);
}
I main(){
#ifndef ETHANKIM8683
  freopen("gathering.in","r",stdin);
  freopen("gathering.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    incs[a].push_back(b);
  }
  for(I i=0;i<n;i++){
    if(dfs1(i)){
      for(I j=0;j<n;j++)printf("0\n");
      exit(0);
    }
  }
  fill_n(ress,n,1);
  dfs2(0,0),dfs4(0,0);
  for(I i=0;i<n;i++)printf("%i\n",ress[i]);
}