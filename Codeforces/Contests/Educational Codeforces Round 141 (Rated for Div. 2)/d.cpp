#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=300;
const I A=300;
const Lli MOD=998244353;
I a_arr[N];
Lli dp[N+1][N*A+N*A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[1][N*A+a_arr[1]]=1;
  for(I i=1;i+1<n;i++)for(I j=-N*A;j<=N*A;j++){
    I a=a_arr[i+1];
    if(j){
      (dp[i+1][N*A+a-j]+=dp[i][N*A+j])%=MOD;
      (dp[i+1][N*A+a+j]+=dp[i][N*A+j])%=MOD;
    }else{
      (dp[i+1][N*A+a]+=dp[i][N*A+j])%=MOD;
    }
  }
  Lli res=0;
  for(I i=-N*A;i<=N*A;i++)(res+=dp[n-1][N*A+i])%=MOD;
  printf("%lli\n",res);
}