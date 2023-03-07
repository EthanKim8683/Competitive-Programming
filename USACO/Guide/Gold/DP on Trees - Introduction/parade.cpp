#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=200000;
const I MIN=-1e9;
vector<I>adjs[N];
I dp[N][3];
I res=0;
void dfs(I a,I p=-1){
  dp[a][0]=0;
  for(auto b:adjs[a])if(b!=p)dfs(b,a),dp[a][0]++;
  for(auto b:adjs[a])if(b!=p){
    dp[a][2]=max(dp[a][2],max(max(dp[b][0],dp[b][1]),0)-1+dp[a][1]);
    dp[a][1]=max(dp[a][1],max(max(dp[b][0],dp[b][1]),0)-1+dp[a][0]);
    res=max(res,max(dp[b][1],dp[b][2])+1);
  }
  res=max(res,max(dp[a][1],dp[a][2]));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,MIN);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  printf("%i\n",res);
}