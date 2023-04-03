#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I MAX=1e9;
I typs[N];
vector<I>adjs[N];
I sizs[N];
I dp[N][2];
void dfs(I a){
  if(typs[a]==0){
    B lea=1;
    for(auto b:adjs[a]){
      dfs(b),lea=0;
      sizs[a]+=sizs[b];
      dp[a][1]+=dp[b][1];
    }
    if(lea)sizs[a]=1;
    dp[a][0]=sizs[a]-dp[a][1]-1;
  }
  if(typs[a]==1){
    dp[a][0]=MAX;
    B lea=1;
    for(auto b:adjs[a]){
      dfs(b),lea=0;
      sizs[a]+=sizs[b];
      dp[a][0]=min(dp[a][0],dp[b][0]);
    }
    if(lea)dp[a][0]=0,sizs[a]=1;
    dp[a][1]=sizs[a]-dp[a][0]-1;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>typs[i];
  for(I i=1;i<n;i++){
    I f;cin>>f,f--;
    adjs[f].push_back(i);
  }
  dfs(0);
  printf("%i\n",dp[0][1]+1);
}