#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=10;

Lli dp[N+1][2][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)dp[i][j][k]=0;
    dp[0][0][0]=1;
    for(I i=0;i<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++){
      I d=s[i]-'0';
      dp[i+1][k][0]+=dp[i][j][k]*(j?10-(d+1):d+1);
      dp[i+1][k][1]+=dp[i][j][k]*(j?10-(d+1-1):d+1-1);
    }
    printf("%lli\n",dp[n][0][0]-2);
  }
}