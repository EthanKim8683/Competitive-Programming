#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I LOGN=17;
const I MAX=1e9;
vector<I>adjs[N];
I sizs[N];
B viss[N];
I ancs[N][LOGN];
I diss[N];
I inds[N],spas[2*N][LOGN+1];
I tim=0;
I n;
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I p=-1){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  if(p==-1)p=a;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[p][i-1];
  for(auto b:adjs[a])if(!viss[b])dfs3(b,a);
}
void dfs4(I a,I p=-1,I d=0){
  spas[inds[a]=tim++][0]=d;
  for(auto b:adjs[a])if(b!=p){
    dfs4(b,a,d+1);
    spas[tim++][0]=d;
  }
}
void bld(){
  for(I i=1;i<LOGN+1;i++)for(I j=0;j+(1<<(i-1))<tim;j++)spas[j][i]=min(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return min(spas[l][d],spas[r-(1<<d)][d]);
}
I dis(I a,I b){
  a=inds[a],b=inds[b];
  if(a>b)swap(a,b);
  return spas[a][0]+spas[b][0]-2*qry(a,b+1);
}
void col(I i){
  diss[i]=0;
  for(I j=0;j<LOGN;j++){
    I k=ancs[i][j];
    diss[k]=min(diss[k],dis(i,k));
  }
}
I slv(I i){
  I res=diss[i];
  for(I j=0;j<LOGN;j++){
    I k=ancs[i][j];
    res=min(res,diss[k]+dis(i,k));
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs3(0),dfs4(0);
  bld();
  fill_n(diss,n,MAX);
  col(0);
  while(m--){
    I t,v;cin>>t>>v,v--;
    if(t==1)col(v);
    if(t==2)printf("%i\n",slv(v));
  }
}