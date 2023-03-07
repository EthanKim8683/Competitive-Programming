#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=400;
const I K=N;
const I MAX=1e9;
vector<pair<I,I>>adjs[N];
I pars[N];
vector<pair<I,I>>dp[N][K+1];
tuple<I,I,I>acc={MAX,-1,-1};
vector<I>ress;
I k;
void dfs1(I a,I p=-1){
  pars[a]=p;
  dp[a][1].push_back({0,-1});
  for(I i=2;i<=k;i++)dp[a][i].push_back({MAX,-1});
  for(auto[b,i]:adjs[a])if(b!=p){
    dfs1(b,a);
    acc=min(acc,{dp[b][k].back().first+1,b,i});
    for(I i=k;i>=1;i--){
      for(I j=1;i+j<=k;j++)dp[a][i+j].back()=min(dp[a][i+j].back(),{dp[a][i].back().first+dp[b][j].back().first,j});
      dp[a][i].push_back({dp[a][i].back().first+1,0});
    }
  }
}
void dfs2(I a,I i,I p){
  I j=dp[a][i].size()-1;
  while(adjs[a].size()){
    auto[b,cur]=adjs[a].back();adjs[a].pop_back();
    if(b==p)continue;
    auto[sum,k]=dp[a][i][j--];
    if(k)dfs2(b,k,a),i-=k;
    else ress.push_back(cur);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
  }
  dfs1(0);
  acc=min(acc,{dp[0][k].back().first,0,-1});
  auto[res,a,i]=acc;
  if(i!=-1)ress.push_back(i);
  dfs2(a,k,pars[a]);
  printf("%i\n",res);
  for(auto i:ress)printf("%i ",i+1);
}