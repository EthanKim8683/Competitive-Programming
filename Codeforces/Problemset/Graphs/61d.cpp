#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

Lli dp1[N],dp2[N];
vector<pair<I,I>>adjs[N];
Lli res=MAX;

void dfs1(I a,I p=-1){
  for(auto[b,w]:adjs[a])if(b!=p){
    dfs1(b,a);
    dp1[a]+=dp1[b]+w;
  }
}

void dfs2(I a,I p=-1){
  B lef=1;
  for(auto[b,w]:adjs[a])if(b!=p){
    dp2[b]=dp2[a]+(dp1[a]-(dp1[b]+w))*2+w;
    dfs2(b,a),lef=0;
  }
  if(lef)res=min(res,dp2[a]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y,w;cin>>x>>y>>w,x--,y--;
    adjs[x].push_back({y,w});
    adjs[y].push_back({x,w});
  }
  dfs1(0),dfs2(0);
  printf("%lli\n",res);
  return 0;
}