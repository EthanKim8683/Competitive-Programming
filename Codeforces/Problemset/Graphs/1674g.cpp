#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs1[N],adjs2[N];
vector<I>tops;
B viss[N];
I dp[N];

void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs1[a])dfs(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs1[u].push_back(v);
    adjs2[v].push_back(u);
  }
  for(I i=0;i<n;i++)dfs(i);
  reverse(tops.begin(),tops.end());
  fill_n(dp,n,1);
  for(I i=0;i<n;i++){
    I a=tops[i];
    if(adjs2[a].size()<=1)continue;
    for(auto b:adjs2[a]){
      if(adjs1[b].size()<=1)continue;
      dp[a]=max(dp[a],dp[b]+1);
    }
  }
  I res=0;
  for(I i=0;i<n;i++)res=max(res,dp[i]);
  printf("%i\n",res);
}