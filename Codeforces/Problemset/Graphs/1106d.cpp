#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
vector<I>ress;
B viss[N];
priority_queue<I>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  viss[0]=true;
  que.push(0);
  while(que.size()){
    I a=-que.top();que.pop();
    ress.push_back(a);
    for(auto b:adjs[a]){
      if(viss[b])continue;
      viss[b]=true;
      que.push(-b);
    }
  }
  for(auto res:ress)printf("%i ",res+1);
  return 0;
}