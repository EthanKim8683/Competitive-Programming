#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const Lli MAX=1e18;
I a_arr[N];
I lows[N];
deque<I>ques;
Lli dp[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,c;cin>>n>>c;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<c;i++){
    while(ques.size()&&a_arr[ques.back()]>=a_arr[i])ques.pop_back();
    ques.push_back(i);
  }
  lows[0]=a_arr[ques.front()];
  for(I i=c;i<n;i++){
    while(ques.size()&&ques.front()<=i-c)ques.pop_front();
    while(ques.size()&&a_arr[ques.back()]>=a_arr[i])ques.pop_back();
    ques.push_back(i);
    lows[i-c+1]=a_arr[ques.front()];
  }
  fill_n(dp,n+1,MAX);
  dp[0]=accumulate(a_arr,a_arr+n,0ll);
  for(I i=0;i<n;i++){
    if(i+c<=n)dp[i+c]=min(dp[i+c],dp[i]-lows[i]);
    dp[i+1]=min(dp[i+1],dp[i]);
  }
  printf("%lli\n",dp[n]);
}