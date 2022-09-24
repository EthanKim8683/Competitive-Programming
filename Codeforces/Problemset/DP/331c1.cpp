#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e6;
const I MAX=1e9;

I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp,n,MAX);
  dp[n]=0;
  for(I i=n;i>=0;i--)
    for(I t=i;t;t/=10)if(i-t%10>=0)dp[i-t%10]=min(dp[i-t%10],dp[i]+1);
  printf("%i\n",dp[0]);
}