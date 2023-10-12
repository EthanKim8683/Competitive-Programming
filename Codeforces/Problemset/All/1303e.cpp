#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=400;
const I M=400;
I dp[N+1][M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    S t;cin>>t;
    I n=s.size(),m=t.size();
    B res=0;
    for(I i=0;i<=m;i++){
      for(I j=0;j<=n;j++)for(I k=0;k<=i;k++)dp[j][k]=-1;
      dp[0][0]=i;
      for(I j=0;j<n;j++)for(I k=0;k<=i;k++)if(dp[j][k]!=-1){
        I l=dp[j][k];
        if(k<i&&s[j]==t[k])dp[j+1][k+1]=max(dp[j+1][k+1],dp[j][k]);
        if(l<m&&s[j]==t[l])dp[j+1][k]=max(dp[j+1][k],dp[j][k]+1);
        dp[j+1][k]=max(dp[j+1][k],dp[j][k]);
      }
      res|=dp[n][i]==m;
    }
    printf("%s\n",res?"YES":"NO");
  }
}