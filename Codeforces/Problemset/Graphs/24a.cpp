#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I MAX=1e9;

const I N=100;

vector<pair<I,I>>adjs[N];
B viss[N];

I dfs(I a,I p){
  if(viss[a])return 0;
  viss[a]=true;
  I res=0;
  for(auto[b,d]:adjs[a])if(b!=p)res+=dfs(b,a)+d;
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b,c;cin>>a>>b>>c,a--,b--;
    adjs[a].push_back({b,0});
    adjs[b].push_back({a,c});
  }
  I res=MAX;
  for(auto[b,d]:adjs[0]){
    fill_n(viss,n,false);
    viss[0]=true;
    res=min(res,dfs(b,0)+d);
  }
  printf("%i\n",res);
  return 0;
}