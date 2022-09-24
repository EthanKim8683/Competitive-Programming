#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1000;

map<pair<I,S>,vector<pair<I,S>>>adjs;
priority_queue<pair<I,pair<I,S>>>que;
map<S,pair<I,I>>viss;

void add(I d,pair<I,S>a){
  auto[av,as]=a;
  if(viss.find(as)!=viss.end()){
    if(d>viss[as].first)return;
    if(av<=viss[as].second)return;
  }
  viss[as]={d,av};
  que.push({-d,a});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  pair<I,S>r;
  for(I i=0;i<n;i++){
    S as;I av;cin>>as>>av;
    if(i==0)r={av,as};
    I d;cin>>d;
    for(I j=0;j<d;j++){
      S bs;I bv;cin>>bs>>bv;
      adjs[{av,as}].push_back({bv,bs});
    }
  }
  add(0,r);
  while(que.size()){
    auto[d,a]=que.top();que.pop();
    auto[av,as]=a;
    if(av!=viss[as].second)continue;
    for(auto b:adjs[a])add(-d+1,b);
  }
  viss.erase(r.second);
  printf("%i\n",viss.size());
  for(auto[bs,bp]:viss)
    printf("%s %i\n",bs.c_str(),bp.second);
  return 0;
}