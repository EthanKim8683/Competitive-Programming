#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=500;
vector<pair<I,I>>adjs1[N],adjs2[N];
vector<I>tops;
B viss[N];
B curs[N];
I cols[N];
void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto[b,i]:adjs1[a])dfs1(b);
  tops.push_back(a);
}
void dfs2(I a){
  if(viss[a])return;
  viss[a]=1,curs[a]=1;
  for(auto[b,i]:adjs2[a])dfs2(b);
}
B dfs3(I a,I j){
  if(cols[a]==1)return 1;
  if(cols[a]==2)return 0;
  cols[a]=1;
  for(auto[b,i]:adjs1[a])if(i!=j&&dfs3(b,j))return 1;
  cols[a]=2;
  return 0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs1[u].push_back({v,i});
    adjs2[v].push_back({u,i});
  }
  B vld=1;
  for(I i=0;i<n;i++)vld&=!dfs3(i,-1);
  if(vld)printf("YES"),exit(0);
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  for(auto i:tops)if(!viss[i]){
    fill_n(curs,n,0),dfs2(i);
    for(I j=0;j<n;j++)if(curs[j]){
      I cnt=0,rem;
      for(auto[k,l]:adjs1[j])if(curs[k])cnt++,rem=l;
      if(cnt!=1)continue;
      B vld=1;
      fill_n(cols,n,0);
      for(I k=0;k<n;k++)vld&=!dfs3(k,rem);
      if(vld)printf("YES"),exit(0);
    }
  }
  printf("NO");
}