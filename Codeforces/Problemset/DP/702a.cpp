#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
I dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp,n,1);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i+1<n;i++)
    if(a_arr[i+1]>a_arr[i])
      dp[i+1]=max(dp[i+1],dp[i]+1);
  printf("%i",*max_element(dp,dp+n));
}