#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
vector<I>adjs[N];
I sizs[N];
B viss[N];
I segs[2*N];
I n,k1,k2;
Lli res=0;
void upd(I i,I v){
  for(segs[i+=n]+=v;i>1;i>>=1)segs[i>>1]=segs[i]+segs[i^1];
}
I qry(I l,I r){
  I res=0;
  for(l=max(l,0)+n,r=min(r,n)+n;l<r;l>>=1,r>>=1){
    if(l&1)res+=segs[l++];
    if(r&1)res+=segs[--r];
  }
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
void dfs3(I a,I p,I d){
  res+=qry(k1-d,k2-d+1);
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs3(b,a,d+1);
}
void dfs4(I a,I p,I d){
  upd(d,1);
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs4(b,a,d+1);
}
void dfs5(I a,I p,I d){
  upd(d,-1);
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs5(b,a,d+1);
}
void dfs6(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  for(auto b:adjs[a])if(!viss[b])dfs3(b,a,1),dfs4(b,a,1);
  for(auto b:adjs[a])if(!viss[b])dfs5(b,a,1);
  for(auto b:adjs[a])if(!viss[b])dfs6(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k1>>k2;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  upd(0,1);
  dfs6(0);
  printf("%lli\n",res);
}