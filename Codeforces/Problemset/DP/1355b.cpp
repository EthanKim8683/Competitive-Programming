#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I e_arr[N];
I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>e_arr[i];
    sort(e_arr,e_arr+n,greater<I>());
    fill_n(dp,n+1,0);
    for(I i=0;i<n;i++){
      I e=e_arr[i];
      dp[i+e]=max(dp[i+e],dp[i]+1);
      dp[i+1]=max(dp[i+1],dp[i]);
    }
    printf("%i\n",dp[n]);
  }
}