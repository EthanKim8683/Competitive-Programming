#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=100000;

vector<I>adjs[N];
B viss[N];

B dfs(I a,I p=-1){
  if(viss[a])return true;
  viss[a]=true;
  B res=false;
  for(auto b:adjs[a])
    if(b!=p)res|=dfs(b,a);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  I res=0;
  for(I i=0;i<n;i++)
    if(!viss[i])res+=!dfs(i);
  printf("%i\n",res);
  return 0;
}