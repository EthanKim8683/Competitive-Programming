#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=5000;
const I MIN=-1e9;

C chrs[]="aba";
I dp[N+1][3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*3,MIN);
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++){
    C c=s[i];
    dp[i][0]=max(dp[i][0],0);
    for(I j=0;j<3;j++)for(I k=j;k<3;k++)
      dp[i+1][k]=max(dp[i+1][k],dp[i][j]+(c==chrs[k]));
  }
  I res=MIN;
  for(I i=0;i<3;i++)res=max(res,dp[n][i]);
  printf("%i\n",res);
}