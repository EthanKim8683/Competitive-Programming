#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I degs[N];
vector<I>adjs[N];
B viss[N];
queue<I>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
    degs[u]++,degs[v]++;
  }
  I r=0;
  for(I i=1;i<n;i++)
    if(degs[i]>degs[r])r=i;
  que.push(r),viss[r]=true;
  while(que.size()){
    I a=que.front();que.pop();
    for(auto b:adjs[a]){
      if(viss[b])continue;
      que.push(b),viss[b]=true;
      printf("%i %i\n",a+1,b+1);
    }
  }
  return 0;
}