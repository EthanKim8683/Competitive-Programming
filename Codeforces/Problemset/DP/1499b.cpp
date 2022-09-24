#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=100;
const I MAX=1e9;

B dp[N+1][2][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)dp[i][j][k]=0;
    dp[0][0][1]=dp[0][1][1]=1;
    for(I i=0;i<n;i++){
      if(s[i]=='1'){
        dp[i+1][0][0]|=dp[i][0][1];
        dp[i+1][1][1]|=dp[i][1][0];
        dp[i+1][1][1]|=dp[i][1][1];
      }else{
        dp[i+1][1][0]|=dp[i][1][1];
        dp[i+1][0][1]|=dp[i][0][0];
        dp[i+1][0][1]|=dp[i][0][1];
      }
      dp[i+1][1][0]|=dp[i][0][1];
    }
    I res=0;
    for(I i=0;i<2;i++)for(I j=0;j<2;j++)res|=dp[n][i][j];
    printf("%s\n",res?"YES":"NO");
  }
}