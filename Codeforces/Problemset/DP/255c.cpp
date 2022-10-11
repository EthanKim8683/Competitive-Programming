#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=4000;

I b_arr[N];
I vals[N];
I dp[N][N];
vector<I>inds[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>b_arr[i];
  copy_n(b_arr,n,vals);
  sort(vals,vals+n);
  for(I i=0;i<n;i++)b_arr[i]=lower_bound(vals,vals+n,b_arr[i])-vals;
  for(I i=0;i<n;i++)inds[b_arr[i]].push_back(i);
  I res=0;
  for(I i=0;i<n;i++){
    I a=b_arr[i];
    for(I j=0;j<n;j++){
      I b=b_arr[j];
      res=max(res,dp[i][b]);
      auto it=upper_bound(inds[b].begin(),inds[b].end(),i);
      if(it==inds[b].end())continue;
      dp[*it][a]=max(dp[*it][a],dp[i][b]+1);
    }
  }
  printf("%i\n",res+1);
}