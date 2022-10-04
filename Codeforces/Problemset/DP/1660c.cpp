#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=2e5;
const I MAX=1e9;

I dp[N+1][26+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)for(I j=0;j<=26;j++)dp[i][j]=MAX;
    dp[0][26]=0;
    for(I i=0;i<n;i++){
      I c=s[i]-'a';
      dp[i+1][26]=min(dp[i+1][26],dp[i][c]);
      dp[i+1][c]=min(dp[i+1][c],dp[i][26]);
      for(I j=0;j<=26;j++)dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
    }
    printf("%i\n",dp[n][26]);
  }
}