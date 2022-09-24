#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<tuple>

using namespace std;

using I=int;

const I N=1e5;
const I K=1e5;
const I MAX=1e9;

vector<pair<I,I>>adjs[N];
pair<I,I>diss[N];
pair<I,I>rous[K];
priority_queue<tuple<I,I,I>>que;

void add(I d,I t,I a){
  auto[pd,pt]=diss[a];
  if(d>pd)return;
  if(d==pd&&t<=pt)return;
  diss[a]={d,t};
  que.push({-d,t,a});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(diss,n,pair<I,I>{MAX,0});
  for(I i=0;i<m;i++){
    I u,v,x;cin>>u>>v>>x,u--,v--;
    adjs[u].push_back({v,x});
    adjs[v].push_back({u,x});
  }
  for(I i=0;i<k;i++){
    I s,y;cin>>s>>y,s--;
    add(y,0,s);
  }
  add(0,1,0);
  I res=k;
  while(que.size()){
    auto[d,t,a]=que.top();que.pop();
    auto[pd,pt]=diss[a];
    if((d=-d)!=pd)continue;
    if(t!=pt)continue;
    if(!t)res--;
    for(auto[b,x]:adjs[a])add(d+x,1,b);
  }
  printf("%i\n",res);
  return 0;
}