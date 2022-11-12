#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=500;
const I M=500;
const I B=500;

I a_arr[N];
Lli dp[M+1][B+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,b,x;cin>>n>>m>>b>>x;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=m;j++)for(I k=0;k<=b;k++){
    I a=a_arr[i];
    if(j+1<=m&&k+a<=b)(dp[j+1][k+a]+=dp[j][k])%=x;
  }
  Lli res=0;
  for(I i=0;i<=b;i++)(res+=dp[m][i])%=x;
  printf("%lli\n",res);
}