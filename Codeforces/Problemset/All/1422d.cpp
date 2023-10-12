#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=1e5;
const Lli MAX=1e18;
pair<I,I>locs[M];
vector<I>cpss[2];
Lli diss[2][M];
vector<I>adjs[2][M];
priority_queue<tuple<Lli,I,I>>ques;
pair<I,I>cps(pair<I,I>loc){
  auto[x,y]=loc;
  x=lower_bound(cpss[0].begin(),cpss[0].end(),x)-cpss[0].begin();
  y=lower_bound(cpss[1].begin(),cpss[1].end(),y)-cpss[1].begin();
  return{x,y};
}
void add(Lli d,I i,I j){
  if(d>=diss[i][j])return;
  ques.push({-(diss[i][j]=d),i,j});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0],&diss[0][0]+2*M,MAX);
  I n,m;cin>>n>>m;
  I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y;
    locs[i]={x,y};
    cpss[0].push_back(x);
    cpss[1].push_back(y);
  }
  for(I i=0;i<2;i++){
    sort(cpss[i].begin(),cpss[i].end());
    cpss[i].erase(unique(cpss[i].begin(),cpss[i].end()),cpss[i].end());
  }
  for(I i=0;i<m;i++){
    auto[x,y]=locs[i]=cps(locs[i]);
    adjs[0][x].push_back(y);
    adjs[1][y].push_back(x);
    add(abs(x1-cpss[0][x]),0,x);
    add(abs(y1-cpss[1][y]),1,y);
  }
  while(ques.size()){
    auto[d,i,j]=ques.top();ques.pop();
    if((d=-d)!=diss[i][j])continue;
    for(auto k:adjs[i][j])add(d,!i,k);
    if(j-1>=0)add(d+cpss[i][j]-cpss[i][j-1],i,j-1);
    if(j+1<cpss[i].size())add(d+cpss[i][j+1]-cpss[i][j],i,j+1);
  }
  Lli res=abs(x1-x2)+abs(y1-y2);
  for(I i=0;i<m;i++){
    auto[x,y]=locs[i];
    res=min(res,diss[0][x]+abs(x2-cpss[0][x])+abs(y2-cpss[1][y]));
  }
  printf("%lli\n",res);
}
/*
if we call each row and column a node, the instant movement locations
represent edges between those nodes

we can use Dijkstra's to find the shortest path between Yura's initial
position and his home
*/