#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I K=1e5;

vector<pair<I,I>>adjs[N];
B viss1[K];
B viss2[N];
I cnt=0;

void dfs(I a){
  if(viss2[a])return;
  viss2[a]=1;
  for(auto[b,i]:adjs[a]){
    if(viss1[i])continue;
    viss1[i]=1;
    cnt+=viss2[b];
    dfs(b);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<k;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
  }
  for(I i=0;i<n;i++)dfs(i);
  printf("%i\n",cnt);
  return 0;
}