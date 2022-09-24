#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=5000;

vector<I>adjs[N];
vector<I>tops;
B viss[N];

void dfs1(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs1(b);
  tops.push_back(a);
}

void dfs2(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs2(b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,s;cin>>n>>m>>s,s--;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
  }
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  fill_n(viss,n,0);
  I res=0;
  dfs2(s);
  for(auto i:tops)if(!viss[i])
    dfs2(i),res++;
  printf("%i\n",res);
  return 0;
}