#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<tuple>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

vector<pair<I,I>>adjs1[N],adjs2[N];
Lli diss[N][2];
priority_queue<tuple<Lli,I,I>>que;

void add(Lli d,I a,I t){
  if(d>=diss[a][t])return;
  que.push({-(diss[a][t]=d),a,t});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(Lli),MAX);
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs1[u].push_back({v,w});
    adjs2[v].push_back({u,w});
  }
  add(0,0,0);
  while(que.size()){
    auto[d,a,t]=que.top();que.pop();
    if((d*=-1)!=diss[a][t])continue;
    if(!t)for(auto[b,w]:adjs1[a])add(d+w,b,0);
    for(auto[b,w]:adjs2[a])add(d+w,b,1);
  }
  for(I i=1;i<n;i++){
    Lli res=min(diss[i][0],diss[i][1]);
    if(res==MAX)printf("-1 ");
    else printf("%lli ",res);
  }
  return 0;
}