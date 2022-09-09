#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MIN=-1e18;

I a_arr[N];
vector<I>adjs[N];
Lli dp[N][2];
Lli res=MIN;

void dfs(I a,I p=-1){
  I cnt=0;
  dp[a][0]=a_arr[a];
  dp[a][1]=MIN;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    if(dp[a][1]!=MIN)res=max(res,dp[a][1]+dp[b][1]);
    dp[a][0]+=dp[b][0];
    dp[a][1]=max(dp[a][1],dp[b][1]);
  }
  dp[a][1]=max(dp[a][1],dp[a][0]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0);
  if(res==MIN)printf("Impossible\n");
  else printf("%lli\n",res);
  return 0;
}