#include<iostream>
#include<cstdio>
#include<queue>
#include<set>

using namespace std;

using I=int;

const I N=100;

set<I>adjs[N];
queue<pair<I,I>>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].insert(b);
    adjs[b].insert(a);
  }
  for(I i=0;i<n;i++)
    if(adjs[i].size()==1)que.push({i,1});
  I res=0;
  while(!que.empty()){
    auto[a,d]=que.front();que.pop();
    if(adjs[a].size()!=1)continue;
    res=max(res,d);
    for(auto b:adjs[a]){
      adjs[b].erase(a);
      if(adjs[b].size()==1)que.push({b,d+1});
    }
  }
  printf("%i\n",res);
  return 0;
}