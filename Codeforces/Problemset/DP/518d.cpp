#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I N=2000;
const I T=2000;

Lf dp[T+1][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lf p;I t;cin>>n>>p>>t;
  dp[0][0]=1;
  for(I i=0;i<t;i++)for(I j=0;j<=n;j++){
    if(j+1<=n){
      dp[i+1][j]+=dp[i][j]*(1-p);
      dp[i+1][j+1]+=dp[i][j]*p;
    }else{
      dp[i+1][j]+=dp[i][j];
    }
  }
  Lf res=0;
  for(I i=0;i<=n;i++)res+=i*dp[t][i];
  printf("%Lf\n",res);
}