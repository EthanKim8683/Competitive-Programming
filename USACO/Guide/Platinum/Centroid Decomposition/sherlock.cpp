#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I M=N-3;
pair<I,I>rngs[M+1];
vector<I>adjs[M+1];
I segs[2*N];
I sizs[M+1];
B viss[M+1];
I ress[M+1];
I inds[M+1];
I n;
B cmp1(pair<I,I>a,pair<I,I>b){
  return a.first-a.second>b.first-b.second;
}
B cmp2(I a,I b){
  return rngs[a]<rngs[b];
}
void upd(I l,I r,I x){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs[l++]=x;
    if(r&1)segs[--r]=x;
  }
}
I qry(I i){
  I res=0;
  for(i+=n;i>0;i>>=1)res=max(res,segs[i]);
  return res;
}
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I d=1){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  ress[a]=d;
  for(auto b:adjs[a])if(!viss[b])dfs3(b,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    if(a>b)swap(a,b);
    rngs[i]={b,a};
  }
  rngs[m]={n-1,0};
  sort(rngs,rngs+m+1,cmp1);
  for(I i=1;i<m+1;i++){
    auto[b,a]=rngs[i];
    I j=qry(a);
    adjs[i].push_back(j);
    adjs[j].push_back(i);
    upd(a,b,i);
  }
  dfs3(0);
  iota(inds,inds+m+1,0);
  sort(inds,inds+m+1,cmp2);
  for(I i=0;i<m+1;i++)printf("%i ",ress[inds[i]]);
}
