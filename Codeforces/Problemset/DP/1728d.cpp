#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=2000;

I dp[N+1][N+1];

I cmb(I x,C a,C b){
  if(x==0)return 0;
  if(x==2)return 2;
  if(a<b)return 0;
  if(a>b)return 2;
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)dp[0][i]=1;
    for(I i=2;i<=n;i+=2)for(I j=0;j+i<=n;j++){
      dp[i][j]=2;
      if(dp[i-2][j+0]>=dp[i-2][j+1])dp[i][j]=min(dp[i][j],cmb(dp[i-2][j+0],s[j+i-1],s[j+i-2]));
      if(dp[i-2][j+1]>=dp[i-2][j+0])dp[i][j]=min(dp[i][j],cmb(dp[i-2][j+1],s[j+i-1],s[j]));
      if(dp[i-2][j+1]>=dp[i-2][j+2])dp[i][j]=min(dp[i][j],cmb(dp[i-2][j+1],s[j],s[j+i-1]));
      if(dp[i-2][j+2]>=dp[i-2][j+1])dp[i][j]=min(dp[i][j],cmb(dp[i-2][j+2],s[j],s[j+1]));
    }
    printf("%s\n",(S[]){"Alice","Draw","Bob"}[dp[n][0]].c_str());
  }
}