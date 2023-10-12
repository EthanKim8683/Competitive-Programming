#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I M=2e5;
const I MAX=1e9;
map<pair<I,I>,I>edgs;
vector<pair<I,I>>adjs[N];
I rems[N];
I diss[N];
priority_queue<tuple<I,I,I,I>>ques;
void add1(I d,I a,I cst){
  rems[a]-=cst,d+=rems[a];
  if(d>=diss[a])return;
  ques.push({-(diss[a]=d),1,a,-1});
}
void add2(I d,I a,I cst){
  ques.push({-d,0,a,cst});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I v,u;cin>>v>>u,v--,u--;
    if(v!=n-1)edgs[{v,u}]++;
  }
  for(auto[edg,cst]:edgs){
    auto[v,u]=edg;
    adjs[u].push_back({v,cst});
    rems[v]+=cst;
  }
  fill_n(diss,n,MAX);
  add1(0,n-1,0);
  while(ques.size()){
    auto[d,t,a,cst]=ques.top();ques.pop();
    d=-d;
    if(t==0)add1(d,a,cst);
    if(t==1){
      if(d!=diss[a])continue;
      for(auto[b,cst]:adjs[a])add2(d+1,b,cst);
    }
  }
  printf("%i\n",diss[0]);
}
/*
we can use Dijkstra's, factoring in the cost of removing edges resulting in
greater distances to city n
*/