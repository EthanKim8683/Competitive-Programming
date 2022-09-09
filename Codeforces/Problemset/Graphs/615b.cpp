#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=100000;

vector<I>adjs[N];
B viss[N];
I lens[N];
I degs[N];
Lli res=0;

I dfs(I a){
  if(viss[a])return lens[a];
  viss[a]=true;
  I len=1;
  for(auto b:adjs[a])len=max(len,dfs(b)+1);
  res=max(res,(Lli)len*degs[a]);
  return lens[a]=len;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    degs[u]++,degs[v]++;
    adjs[max(u,v)].push_back(min(u,v));
  }
  for(I i=0;i<n;i++)dfs(i);
  printf("%lli\n",res);
  return 0;
}