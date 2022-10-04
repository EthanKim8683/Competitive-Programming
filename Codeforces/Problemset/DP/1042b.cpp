#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I MAX=1e9;

I dp[1<<3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp,1<<3,MAX);
  dp[0]=0;
  for(I i=0;i<n;i++){
    I c;cin>>c;
    S s;cin>>s;
    I msk=0;
    for(auto c:s)msk|=1<<(c-'A');
    for(I i=(1<<3)-1;i>=0;i--)
      dp[i|msk]=min(dp[i|msk],dp[i]+c);
  }
  I res=dp[(1<<3)-1];
  printf("%i\n",res==MAX?-1:res);
}