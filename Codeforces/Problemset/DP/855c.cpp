#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I X=10;
const Lli MOD=1e9+7;
vector<I>adjs[N];
Lli dp[N][X+1][3];
I m;
I k,x;
void dfs(I a,I p=-1){
  dp[a][0][0]=k-1,dp[a][1][1]=1,dp[a][0][2]=m-k;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    for(I j=x;j>=0;j--){
      Lli cnt0=dp[a][j][0],cnt1=dp[a][j][1],cnt2=dp[a][j][2];
      dp[a][j][0]=dp[a][j][1]=dp[a][j][2]=0;
      for(I k=0;j+k<=x;k++){
        (dp[a][j+k][0]+=cnt0*(dp[b][k][0]+dp[b][k][1]+dp[b][k][2]))%=MOD;
        (dp[a][j+k][1]+=cnt1*dp[b][k][0])%=MOD;
        (dp[a][j+k][2]+=cnt2*(dp[b][k][0]+dp[b][k][2]))%=MOD;
      }
    }
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  cin>>k>>x;
  dfs(0);
  Lli res=0;
  for(I i=0;i<=x;i++)for(I j=0;j<3;j++)(res+=dp[0][i][j])%=MOD;
  printf("%lli\n",res);
}