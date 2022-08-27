#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=100000;

vector<I>adjs[N];
I dp[N];
I res=0;

void dfs(I a,I p=-1){
  for(auto b:adjs[a]){
    if(b==p)continue;
    dfs(b,a);
    res=max(res,dp[a]+dp[b]);
    dp[a]=max(dp[a],dp[b]);
  }
  dp[a]++;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  printf("%i\n",res);
  return 0;
}