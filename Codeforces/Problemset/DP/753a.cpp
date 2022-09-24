#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1000;
const I MIN=-1e9;

I dp[N+1][N+1];
I pars[N+1][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(N+1),MIN);
  I n;cin>>n;
  dp[0][0]=0;
  for(I i=1;i<=n;i++){
    for(I j=0;j<=n;j++){
      if(j+i<=n&&dp[i-1][j]+1>dp[i][j+i])dp[i][j+i]=dp[i-1][j]+1,pars[i][j+i]=i;
      if(j+0<=n&&dp[i-1][j]+0>dp[i][j+0])dp[i][j+0]=dp[i-1][j]+0,pars[i][j+0]=0;
    }
  }
  printf("%i\n",dp[n][n]);
  I j=n;
  for(I i=n;i>0;i--){
    I c=pars[i][j];
    if(c)printf("%i ",c);
    j-=c;
  }
}