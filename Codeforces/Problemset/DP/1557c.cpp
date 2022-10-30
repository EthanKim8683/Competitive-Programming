#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const Lli MOD=1e9+7;

const I N=2e5;

Lli dp[N+1][2];
Lli pows[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  pows[1]=1;
  for(I i=1;i<N;i++)pows[i+1]=pows[i]*2%MOD;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<=k;i++)for(I j=0;j<2;j++)dp[i][j]=0;
    dp[0][0]=1;
    if(n%2){
      for(I i=0;i<k;i++){
        (dp[i+1][0]+=dp[i][0]*pows[n])%=MOD;
        (dp[i+1][0]+=dp[i][0])%=MOD;
      }
    }else{
      for(I i=0;i<k;i++){
        (dp[i+1][0]+=dp[i][0]*(pows[n]-1))%=MOD;
        (dp[i+1][1]+=dp[i][0])%=MOD;
        (dp[i+1][1]+=dp[i][1]*2*pows[n])%=MOD;
      }
    }
    printf("%lli\n",(dp[k][0]+dp[k][1])%MOD);
  }
}