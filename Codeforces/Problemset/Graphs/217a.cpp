#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I X=1000;
const I Y=1000;

vector<I>adjs[2][X];
B viss[2][X];
B vlds[X];

void dfs(I a,I c){
  if(viss[c][a])return;
  viss[c][a]=true;
  for(auto b:adjs[c][a])dfs(b,!c);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y,x--,y--;
    vlds[x]=true;
    adjs[0][x].push_back(y);
    adjs[1][y].push_back(x);
  }
  I res=0;
  for(I i=0;i<X;i++){
    if(!vlds[i])continue;
    res+=!viss[0][i];
    dfs(i,0);
  }
  printf("%i\n",res-1);
  return 0;
}