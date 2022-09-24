#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e5;
const I MIN=-1e9;

I msks[N];
I dp[N+1][1<<2];

I cst(I i){
  if(i==0b00)return 0;
  if(i==0b01)return 1;
  if(i==0b10)return 0;
  if(i==0b11)return 2;
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S a;cin>>a;
    S b;cin>>b;
    for(I i=0;i<=n;i++)for(I j=0;j<(1<<2);j++)dp[i][j]=MIN;
    for(I i=0;i<n;i++)msks[i]=1<<(a[i]-'0')|1<<(b[i]-'0');
    dp[0][0]=0;
    for(I i=0;i<n;i++){
      for(I j=0;j<(1<<2);j++){
        dp[i+1][0|msks[i]]=max(dp[i+1][0|msks[i]],dp[i][j]+cst(j));
        dp[i+1][j|msks[i]]=max(dp[i+1][j|msks[i]],dp[i][j]);
      }
    }
    I res=MIN;
    for(I i=0;i<(1<<2);i++)res=max(res,dp[n][i]+cst(i));
    printf("%i\n",res);
  }
}