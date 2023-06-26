#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
const I N=500;
const I MAX=1e9;
I dp[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(N+1),MAX);
  I n;cin>>n;
  S s;cin>>s;
  for(I i=0;i<=n;i++)dp[i][i]=0;
  for(I i=0;i+1<=n;i++)dp[i][i+1]=1;
  for(I i=2;i<=n;i++)for(I j=0;j+i<=n;j++){
    for(I k=1;k<i;k++)dp[j][j+i]=min(dp[j][j+i],dp[j][j+k]+dp[j+k][j+i]);
    for(I k=0;k<i-1;k++)if(s[j+k]==s[j+i-1])dp[j][j+i]=min(dp[j][j+i],dp[j][j+k+1]+dp[j+k+1][j+i-1]);
  }
  printf("%i\n",dp[0][n]);
}