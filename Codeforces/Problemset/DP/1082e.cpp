#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5e5;
const I A=5e5;
const I MAX=1e9;
const I MIN=-MAX;
I a_arr[N];
I dp[A+1];
I cnts[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,c;cin>>n>>c;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(dp,A+1,MAX);
  I res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    dp[a]=min(dp[a],cnts[a]-cnts[c]);
    cnts[a]++;
    if(a==c)continue;
    res=max(res,cnts[a]-cnts[c]-dp[a]);
    dp[a]=min(dp[a],cnts[a]-cnts[c]);
  }
  printf("%i\n",res+cnts[c]);
}