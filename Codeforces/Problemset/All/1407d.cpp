#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I MAX=1e9;
I h_arr[N];
vector<I>lows,upps;
I dp[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  fill_n(dp,n,MAX),dp[0]=0;
  lows.push_back(0);
  upps.push_back(0);
  for(I i=1;i<n;i++){
    I h=h_arr[i];
    dp[i]=min(dp[i],dp[i-1]+1);
    while(lows.size()&&h>h_arr[lows.back()]){
      dp[i]=min(dp[i],dp[lows.back()]+1);
      lows.pop_back();
    }
    while(upps.size()&&h<h_arr[upps.back()]){
      dp[i]=min(dp[i],dp[upps.back()]+1);
      upps.pop_back();
    }
    if(lows.size()){
      dp[i]=min(dp[i],dp[lows.back()]+1);
      if(h==h_arr[lows.back()])lows.pop_back();
    }
    if(upps.size()){
      dp[i]=min(dp[i],dp[upps.back()]+1);
      if(h==h_arr[upps.back()])upps.pop_back();
    }
    lows.push_back(i);
    upps.push_back(i);
  }
  printf("%i\n",dp[n-1]);
}