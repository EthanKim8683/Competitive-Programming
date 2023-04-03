#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=35;
const I H=N;
Lli dp[N+1][H+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,h;cin>>n>>h;
  dp[0][0]=dp[1][1]=1;
  for(I i=2;i<=n;i++)for(I j=0;j<=i-1;j++)for(I k=0;k<=j;k++)for(I l=0;l<=i-1-j;l++)dp[i][max(k,l)+1]+=dp[j][k]*dp[i-1-j][l];
  Lli res=0;
  for(I i=h;i<=n;i++)res+=dp[n][i];
  printf("%lli\n",res);
}