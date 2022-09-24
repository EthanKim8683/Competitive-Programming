#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=19;
const I MAX=1e9;

I dp[N+1][25];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)for(I j=0;j<25;j++)dp[i][j]=MAX;
    dp[0][0]=0;
    for(I i=0;i<n;i++){
      I c=s[i]-'0';
      for(I j=0;j<25;j++){
        dp[i+1][(j*10+c)%25]=min(dp[i+1][(j*10+c)%25],dp[i][j]);
        dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
      }
    }
    printf("%i\n",dp[n][0]);
  }
}