#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=100;
C mats[N][N+1];
vector<I>adjs[N];
I inds[N];
set<I>ress[N];
B viss[N];
I n;
void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  ress[a].insert(a);
  for(auto b:adjs[a]){
    dfs(b);
    ress[a].insert(ress[b].begin(),ress[b].end());
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>mats[i];
    fill_n(viss,n,0);
    fill_n(inds,n,0);
    for(I i=0;i<n;i++)ress[i].clear(),adjs[i].clear();
    for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(mats[i][j]=='1')adjs[j].push_back(i),inds[i]++;
    for(I i=0;i<n;i++)if(inds[i]==0)dfs(i);
    for(I i=0;i<n;i++){
      printf("%i ",ress[i].size());
      for(auto res:ress[i])printf("%i ",res+1);
      printf("\n");
    }
  }
}