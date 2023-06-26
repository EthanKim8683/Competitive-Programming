#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
vector<I>adjs[N];
pair<I,I>dp[N][2];
map<I,I>pars[N];
I ress[N];
void dfs1(I a,I p=-1){
  dp[a][0]={0,-1};
  dp[a][1]={1,-adjs[a].size()};
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    auto[x,y]=max(pair<pair<I,I>,I>{dp[b][0],0},{dp[b][1],1});
    dp[a][0].first+=x.first;
    dp[a][0].second+=x.second;
    dp[a][1].first+=dp[b][0].first;
    dp[a][1].second+=dp[b][0].second;
    pars[a][b]=y;
  }
}
void dfs2(I a,I t,I p=-1){
  if(t==0){
    ress[a]=1;
    for(auto b:adjs[a])if(b!=p)dfs2(b,pars[a][b],a);
  }else{
    ress[a]=adjs[a].size();
    for(auto b:adjs[a])if(b!=p)dfs2(b,0,a);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  if(n==2)printf("2 2\n1 1"),exit(0);
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0);
  auto[x,y]=max(pair<pair<I,I>,I>{dp[0][0],0},{dp[0][1],1});
  dfs2(0,y);
  auto[a,b]=x;
  printf("%i %i\n",a,-b);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}