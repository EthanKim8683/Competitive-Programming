#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

//dijkstra's from all exits
//only push nodes once reachable from two exits

I travel_plan(I n,I m,I r[][2],I l[],I k,I p[]){
  vector<vector<pair<I,I>>>adjs(n);
  for(I i=0;i<m;i++){
    I a=r[i][0],b=r[i][1],d=l[i];
    adjs[a].push_back({b,d});
    adjs[b].push_back({a,d});
  }
  priority_queue<pair<Lli,I>>que;
  vector<I>viss(n,0);
  for(I i=0;i<k;i++){
    viss[p[i]]=2;
    for(auto[b,d]:adjs[p[i]])
      que.push({-d,b});
  }
  while(!que.empty()){
    auto[dis,a]=que.top();
    que.pop();
    if(viss[a]>=2)continue;
    if(++viss[a]!=2)continue;
    if(a==0)return -dis;
    for(auto[b,d]:adjs[a])
      que.push({dis-d,b});
  }
  return -1;
}

#ifdef ETHANKIM8683
#include<iostream>
#include<cstdio>

const I N=100000;
const I M=1000000;
const I K=999999;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;
  cin>>n>>m;
  static I r[M][2];
  for(I i=0;i<m;i++)cin>>r[i][0]>>r[i][1];
  static I l[M];
  for(I i=0;i<m;i++)cin>>l[i];
  I k;
  cin>>k;
  static I p[K];
  for(I i=0;i<k;i++)cin>>p[i];
  printf("%i\n",travel_plan(n,m,r,l,k,p));
  return 0;
}
#endif