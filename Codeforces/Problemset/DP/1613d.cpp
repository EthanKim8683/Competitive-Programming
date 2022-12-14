#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5e5;
const I M=N+1;
const Lli MOD=998244353;
I a_arr[N];
Lli dp[M+1][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I m=n+1;
    for(I i=0;i<=m;i++)for(I j=0;j<2;j++)dp[i][j]=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      if(a+1<=m)(dp[a+1][1]+=dp[a+1][1])%=MOD;
      if(a+1<=m)(dp[a+1][0]+=dp[a+1][0])%=MOD;
      if(a-1>=0)(dp[a-1][1]+=dp[a-1][1])%=MOD;
      if(a-1>=0)(dp[a-1][1]+=dp[a-1][0])%=MOD;
      if(a+1<=m)(dp[a+1][0]+=dp[a+0][0])%=MOD;
      if(a==0)(dp[1][0]+=1)%=MOD;
      if(a==1)(dp[0][1]+=1)%=MOD;
    }
    Lli res=0;
    for(I i=0;i<=m;i++)for(I j=0;j<2;j++)(res+=dp[i][j])%=MOD;
    printf("%lli\n",res);
  }
}