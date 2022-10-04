#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=5000;
const I M=5000;

vector<pair<I,I>>adjs[N];
B viss1[N];
I viss2[N];
I ress[M];
vector<I>tops;
I res=0;

void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=1;
  for(auto[b,i]:adjs[a])dfs1(b);
  tops.push_back(a);
}

void dfs2(I a){
  if(viss2[a])return;
  viss2[a]=1;
  for(auto[b,i]:adjs[a]){
    if(viss2[b]==1)res=ress[i]=1;
    dfs2(b);
  }
  viss2[a]=2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v;
    adjs[u-1].push_back({v-1,i});
  }
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  for(auto i:tops)dfs2(i);
  printf("%i\n",res+1);
  for(I i=0;i<m;i++)printf("%i ",ress[i]+1);
}