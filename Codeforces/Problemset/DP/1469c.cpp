#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I h_arr[N];
pair<I,I>dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>h_arr[i];
    dp[0]={h_arr[0],h_arr[0]};
    B res=1;
    for(I i=1;i<n;i++){
      auto[low,upp]=dp[i-1];
      I h=h_arr[i];
      low=max(low-(k-1),h);
      upp=min(upp+(k-1),h+k-1);
      res&=low<=upp;
      dp[i]={low,upp};
    }
    res&=dp[n-1].first==h_arr[n-1];
    printf("%s\n",res?"YES":"NO");
  }
}