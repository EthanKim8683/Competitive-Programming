#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I H=893;
const I R=2e5;
const I G=2e5;
const Lli MOD=1e9+7;
Lli dp[2][R+1];
B viss[H+1];
I main(){
  I r,g;cin>>r>>g;
  dp[0][r]=1,viss[0]=1;
  Lli res=0;
  for(I i=0,t=0;i<=H;i++,t=!t){
    if(!viss[i])break;
    res=0;
    for(I j=max(r-i*(i+1)/2,0);j<=r;j++){
      I k=r+g-i*(i+1)/2-j;
      if(k<0||j<0)continue;
      (res+=dp[t][j])%=MOD;
      if(j>=i+1)viss[i+1]=1,(dp[!t][j-(i+1)]+=dp[t][j])%=MOD;
      if(k>=i+1)viss[i+1]=1,(dp[!t][j]+=dp[t][j])%=MOD;
      dp[t][j]=0;
    }
  }
  printf("%lli\n",res);
}