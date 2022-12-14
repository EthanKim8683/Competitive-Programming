#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=88;
Lli dp[M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n;cin>>n;
  dp[0]=dp[1]=1;
  for(I i=2;i<=M;i++)dp[i]=dp[i-1]+dp[i-2];
  I j=upper_bound(dp,dp+M+1,n)-dp-2;
  printf("%i\n",j);
}