#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N];
priority_queue<pair<I,I>>dp;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    while(dp.size()&&dp.top().second<=i)dp.pop();
    I cur=dp.size()?dp.top().first:1;
    res=max(res,cur);
    dp.push({cur+1,upper_bound(a_arr,a_arr+n,a*2)-a_arr});
  }
  printf("%i\n",res);
}