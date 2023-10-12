#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I W=50;
const Lli MAX=1e18;
vector<pair<I,I>>adjs[N];
priority_queue<tuple<Lli,I,I>>ques;
Lli diss[N][W+1];
void add(Lli dis,I t,I a){
  if(dis>=diss[a][t])return;
  ques.push({-(diss[a][t]=dis),-t,a});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0],&diss[0][0]+N*(W+1),MAX);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs[u].push_back({v,w});
    adjs[v].push_back({u,w});
  }
  add(0,0,0);
  while(ques.size()){
    auto[dis,t,a]=ques.top();ques.pop();
    if((dis=-dis)!=diss[a][t=-t])continue;
    if(t==0)for(auto[b,w]:adjs[a])add(dis,w,b);
    if(t!=0)for(auto[b,w]:adjs[a])add(dis+(Lli)(t+w)*(t+w),0,b);
  }
  for(I i=0;i<n;i++)printf("%lli ",diss[i][0]==MAX?-1:diss[i][0]);
}