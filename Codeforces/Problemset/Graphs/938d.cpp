#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MAX=1e18;

vector<pair<I,Lli>>adjs[N];
priority_queue<pair<Lli,I>>que;
Lli diss[N];

void add(Lli d,I i){
  if(d>=diss[i])return;
  que.push({-(diss[i]=d),i});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,n,MAX);
  for(I i=0;i<m;i++){
    I u,v;Lli w;cin>>u>>v>>w,u--,v--;
    adjs[u].push_back({v,w});
    adjs[v].push_back({u,w});
  }
  for(I i=0;i<n;i++){
    Lli a;cin>>a;
    add(a,i);
  }
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    if((d*=-1)!=diss[a])continue;
    for(auto[b,w]:adjs[a])add(d+w*2,b);
  }
  for(I i=0;i<n;i++)printf("%lli ",diss[i]);
  return 0;
}