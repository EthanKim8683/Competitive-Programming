#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=2e5;
const Lli MAX=1e18;

Lli dp[N+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,a,b;cin>>n>>a>>b;
    S s;cin>>s;
    for(I i=0;i<=n;i++)for(I j=0;j<2;j++)dp[i][j]=MAX;
    dp[0][0]=b;
    for(I i=0;i<n;i++){
      dp[i+1][1]=min(dp[i+1][1],dp[i][1]+a+2*b);
      if(s[i]=='0'){
        dp[i+1][0]=min(dp[i+1][0],dp[i][0]+a+b);
        dp[i+1][1]=min(dp[i+1][1],dp[i][0]+2*a+2*b);
        dp[i+1][0]=min(dp[i+1][0],dp[i][1]+2*a+b);
      }
    }
    printf("%lli\n",dp[n][0]);
  }
}