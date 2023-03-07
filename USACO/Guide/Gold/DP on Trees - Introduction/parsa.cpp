#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
vector<I>adjs[N];
pair<I,I>rngs[N];
Lli dp[N][2];
void dfs(I a,I p=-1){
  dp[a][0]=dp[a][1]=0;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    dp[a][0]+=max(abs(rngs[a].first-rngs[b].first)+dp[b][0],abs(rngs[a].first-rngs[b].second)+dp[b][1]);
    dp[a][1]+=max(abs(rngs[a].second-rngs[b].first)+dp[b][0],abs(rngs[a].second-rngs[b].second)+dp[b][1]);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n;i++){
      I l,r;cin>>l>>r;
      rngs[i]={l,r};
    }
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    dfs(0);
    printf("%lli\n",max(dp[0][0],dp[0][1]));
  }
}