#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=123456;
const I MAX=1e9;
const I MIN=-1e9;
vector<I>adjs[N];
I inds[N];
B atks[N];
pair<I,I>far;
void dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    atks[a]|=atks[b];
  }
}
void dfs2(I a,I p=-1,I d=0){
  if(!atks[a])return;
  far=max(far,{d,-a});
  for(auto b:adjs[a])if(b!=p)dfs2(b,a,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  I r;
  for(I i=0;i<m;i++){
    cin>>r,r--;
    atks[r]=1;
  }
  dfs1(r);
  I res=0;
  for(I i=0;i<n;i++)res+=atks[i];
  far={MIN,-MAX},dfs2(r);
  auto[dis1,a]=far;a=-a;
  far={MIN,-MAX},dfs2(a);
  auto[dis2,b]=far;b=-b;
  far={MIN,-MAX},dfs2(b);
  auto[dis3,c]=far;c=-c;
  printf("%i\n%i\n",min(b,c)+1,2*(res-1)-dis3);
}