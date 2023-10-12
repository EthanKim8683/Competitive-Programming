#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000;
const I ASUM=10000;
const Lli MOD=1e9+7;
I a_arr[N];
Lli dp[N+1][2*ASUM+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    for(I j=-ASUM;j<=ASUM;j++){
      if(j-a>=-ASUM)(dp[i+1][ASUM+j-a]+=dp[i][ASUM+j])%=MOD;
      if(j+a<=ASUM)(dp[i+1][ASUM+j+a]+=dp[i][ASUM+j])%=MOD;
      if(j-a==0)(res+=dp[i][ASUM+j])%=MOD;
      if(j+a==0)(res+=dp[i][ASUM+j])%=MOD;
    }
    (dp[i+1][ASUM+a]+=1)%=MOD;
    (dp[i+1][ASUM-a]+=1)%=MOD;
    if(a==0)(res+=dp[i][ASUM+0])%=MOD;
  }
  printf("%lli\n",res);
}
/*
knapsack dynamic programming

should be rated 1600-ish
*/