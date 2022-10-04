#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e5;
const I MAX=1e9;

I dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b;cin>>a>>b;
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)dp[i][0]=dp[i][1]=MAX;
    dp[0][0]=0;
    for(I i=0;i<n;i++){
      if(s[i]=='0'){
        dp[i+1][0]=min(dp[i+1][0],dp[i][0]);
        dp[i+1][0]=min(dp[i+1][0],dp[i][1]+a);
        dp[i+1][1]=min(dp[i+1][1],dp[i][1]+b);
      }
      if(s[i]=='1'){
        dp[i+1][1]=min(dp[i+1][1],dp[i][1]);
        dp[i+1][1]=min(dp[i+1][1],dp[i][0]);
      }
    }
    printf("%i\n",min(dp[n][0],dp[n][1]+a));
  }
}