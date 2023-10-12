#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e6;
vector<I>adjs[N];
map<I,I>cnts[N];
pair<I,I>doms[N];
I ress[N];
void dfs(I a,I p=-1,I d=0){
  cnts[a][d]++;
  doms[a]={1,-d};
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a,d+1);
    if(cnts[a].size()<cnts[b].size()){
      swap(cnts[a],cnts[b]);
      swap(doms[a],doms[b]);
    }
    for(auto[dep,cnt]:cnts[b]){
      cnts[a][dep]+=cnt;
      doms[a]=max(doms[a],{cnts[a][dep],-dep});
    }
    cnts[b].clear();
  }
  adjs[a].clear();
  ress[a]=-doms[a].second-d;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs(0);
  for(I i=0;i<n;i++)printf("%i\n",ress[i]);
}
/*
if we small-to-large merge (size equal to maximum depth) at every vertex, we
can keep track of the earliest largest depth and update per merge
*/