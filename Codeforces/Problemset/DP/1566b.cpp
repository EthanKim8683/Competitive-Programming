#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e5;
const I MAX=1e9;

I dp[N+1][1<<2];

I cst(I i){
  if(i==0b00)return 0;
  if(i==0b01)return 1;
  if(i==0b10)return 0;
  if(i==0b11)return 2;
  return MAX;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    for(I i=0;i<=n;i++)for(I j=0;j<(1<<2);j++)dp[i][j]=MAX;
    dp[0][1<<(s[0]-'0')]=0;
    for(I i=0;i<n;i++){
      I c=s[i]-'0';
      for(I j=0;j<(1<<2);j++){
        dp[i+1][0|1<<c]=min(dp[i+1][0|1<<c],dp[i][j]+cst(j));
        dp[i+1][j|1<<c]=min(dp[i+1][j|1<<c],dp[i][j]);
      }
    }
    I res=MAX;
    for(I i=0;i<(1<<2);i++)res=min(res,dp[n][i]+cst(i));
    printf("%i\n",res);
  }
}