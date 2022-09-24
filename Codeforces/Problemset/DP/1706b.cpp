#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I c_arr[N];
set<I>unvs[N+1][2];
I dp[N];
I ress[N+1];
I n;

I dfs(I i){
  if(dp[i])return dp[i];
  auto it=unvs[c_arr[i]][1-i%2].upper_bound(i);
  I res=1;
  if(it!=unvs[c_arr[i]][1-i%2].end())res=max(res,dfs(*it)+1);
  return dp[i]=res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>c_arr[i];
    for(I i=1;i<=n;i++)for(I j=0;j<2;j++)unvs[i][j].clear();
    for(I i=0;i<n;i++)unvs[c_arr[i]][i%2].insert(i);
    fill_n(dp,n,0),fill_n(ress,n+1,0);
    for(I i=0;i<n;i++)ress[c_arr[i]]=max(ress[c_arr[i]],dfs(i));
    for(I i=1;i<=n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}