#include<iostream>
#include<cstdio>
#include<vector>
#include<set>

using namespace std;

using I=int;

const I N=1e5;

vector<pair<I,I>>adjs[N];
set<I>cans;

void dfs(I a,I p=-1,I m=-1){
  for(auto[b,t]:adjs[a]){
    if(b==p)continue;
    I r=m;
    if(t==2){
      auto it=cans.find(m);
      if(it!=cans.end())cans.erase(it);
      cans.insert(b);
      r=b;
    }
    dfs(b,a,r);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y,t;cin>>x>>y>>t,x--,y--;
    adjs[x].push_back({y,t});
    adjs[y].push_back({x,t});
  }
  dfs(0);
  printf("%i\n",cans.size());
  for(auto can:cans)printf("%i ",can+1);
  return 0;
}