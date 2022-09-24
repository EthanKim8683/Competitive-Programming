#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I dp[N][2][2];
I n;

I dfs(I i,I j,I k){
  if(i>=n)return !k;
  if(dp[i][j][k]!=-1)return dp[i][j][k];
  if(j||a_arr[i]==1)return dp[i][j][k]=dfs(i+1,0,!k);
  if(dfs(i,1,!k)==k)return dp[i][j][k]=k;
  if(dfs(i+1,0,!k)==k)return dp[i][j][k]=k;
  return dp[i][j][k]=!k;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)dp[i][j][k]=-1;
    printf("%s\n",dfs(0,0,0)==0?"First":"Second");
  }
}