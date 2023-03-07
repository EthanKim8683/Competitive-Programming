#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=300000;
const I K=N;
const I LOGN=19;
const I MAX=1e9;
vector<I>adjs[N];
I a_arr[K];
I inds[N];
I spas[2*N][LOGN+1];
I rads[N];
I sizs[N];
B viss[N];
I segs[2*N];
I ress[N];
I tim=0;
I n;
void dfs1(I a,I p=-1,I d=0){
  spas[inds[a]=tim++][0]=d;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a,d+1);
    rads[a]=min(rads[a],rads[b]+1);
    spas[tim++][0]=d;
  }
}
void dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    rads[b]=min(rads[b],rads[a]+1);
    dfs2(b,a);
  }
}
void bld(){
  for(I i=1;i<LOGN+1;i++)for(I j=0;j+(1<<(i-1))<tim;j++)spas[j][i]=min(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I dis(I a,I b){
  a=inds[a],b=inds[b];
  if(a>b)swap(a,b);
  I d=31-__builtin_clz(b+1-a);
  return spas[a][0]+spas[b][0]-2*min(spas[a][d],spas[b+1-(1<<d)][d]);
}
void upd(I i,I x){
  if(i>=0)for(segs[i+=n]+=x;i>1;i>>=1)segs[i>>1]=segs[i]+segs[i^1];
}
I qry(I l,I r){
  I res=0;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res+=segs[l++];
    if(r&1)res+=segs[--r];
  }
  return res;
}
I dfs3(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs3(b,a);
  return sizs[a];
}
I dfs4(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs4(b,siz,a);
  return a;
}
void dfs6(I a,I d,I p=-1){
  upd(rads[a]-d,1);
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs6(b,d+1,a);
}
void dfs7(I a,I p=-1,I d=1){
  ress[a]+=qry(d,n);
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs7(b,a,d+1);
}
void dfs8(I a,I d,I p=-1){
  upd(rads[a]-d,-1);
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs8(b,d+1,a);
}
void dfs5(I a){
  a=dfs4(a,dfs3(a));
  viss[a]=1;
  dfs6(a,0);
  for(auto b:adjs[a])if(!viss[b])dfs8(b,1),dfs7(b),dfs6(b,1);
  ress[a]+=qry(0,n);
  dfs8(a,0);
  for(auto b:adjs[a])if(!viss[b])dfs5(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  fill_n(rads,n,MAX);
  for(I i=0;i<k;i++){
    I a;cin>>a,a--;
    rads[a_arr[i]=a]=0;
  }
  dfs1(0),bld(),dfs2(0);
  for(I i=0;i<n;i++){
    I f,p;cin>>f>>p,f--;
    rads[i]=min(rads[i],dis(i,f)-p-1);
  }
  dfs5(0);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}