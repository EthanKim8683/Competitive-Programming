#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;
const I MIN=-1e9;

I dp[N+1][3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*3,MIN);
  S s;cin>>s;
  I n=s.size();
  dp[0][0]=0;
  for(I i=0;i<n;i++){
    I d=s[i]-'0';
    for(I j=0;j<3;j++){
      I k=(j*10+d)%3;
      dp[i+1][k]=max(dp[i+1][k],dp[i][j]+!k);
      dp[i+1][0]=max(dp[i+1][0],dp[i][j]);
    }
  }
  printf("%i\n",dp[n][0]);
}