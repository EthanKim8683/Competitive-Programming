#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=80000;
const I M=80000;
tuple<I,I,I,I>dons[N];
tuple<I,I,I>kims[M];
map<pair<I,I>,I>upps;
vector<tuple<I,I,I>>ques;
set<I>cols[N];
vector<I>adjs[N];
I inds[N];
I ress[N];
void dfs(I a){
  for(auto b:adjs[a]){
    dfs(b);
    if(cols[b].size()>cols[a].size())swap(cols[a],cols[b]);
    for(auto k:cols[b])cols[a].insert(k);
  }
  ress[a]=cols[a].size();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I a,b,c,d;cin>>a>>b>>c>>d;
    dons[i]={a,b,c,d};
    ques.push_back({-a,3,i});
    ques.push_back({-c,1,i});
  }
  for(I i=0;i<m;i++){
    I x,y,k;cin>>x>>y>>k;
    kims[i]={x,y,k};
    ques.push_back({-x,2,i});
  }
  sort(ques.begin(),ques.end());
  while(ques.size()){
    auto[cur,t,i]=ques.back();ques.pop_back();
    if(t==3){
      auto[a,b,c,d]=dons[i];
      upps.insert({{d,0},i});
      auto it=upps.upper_bound({d,0});
      if(it==upps.end())continue;
      I j=it->second;
      if(b<get<1>(dons[j]))continue;
      adjs[j].push_back(i),inds[i]++;
      upps.insert({{b,-1},j});
    }
    if(t==2){
      auto[x,y,k]=kims[i];
      auto it=upps.lower_bound({y,0});
      if(it==upps.end())continue;
      I j=it->second;
      if(y<get<1>(dons[j]))continue;
      cols[j].insert(k);
    }
    if(t==1){
      auto[a,b,c,d]=dons[i];
      upps.erase({d,0});
      auto it=upps.upper_bound({d,0});
      if(it==upps.end())continue;
      I j=it->second;
      if(b<get<1>(dons[j]))continue;
      upps.erase({b,-1});
    }
  }
  for(I i=0;i<n;i++)if(!inds[i])dfs(i);
  for(I i=0;i<n;i++)printf("%i\n",ress[i]);
}