#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=50;
const I M=50;
I a_arr[M];
Lf dp[M+1][N+1][N+1];
Lf bin(I n,I k){
  Lf res=1;
  for(I i=n-k+1;i<=n;i++)res*=i;
  for(I i=1;i<=k;i++)res/=i;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++)cin>>a_arr[i];
  dp[0][0][0]=1;
  for(I i=0;i<m;i++)for(I j=0;j<=n;j++)for(I k=0;k<=n;k++)for(I l=0;j+l<=n;l++){
    I a=a_arr[i];
    dp[i+1][j+l][max(k,(l+a-1)/a)]+=dp[i][j][k]*bin(n-j,l);
  }
  Lf res=0;
  for(I i=0;i<=n;i++)res+=i*dp[m][n][i];
  printf("%.20Lf\n",res*pow(1./m,n));
}
/*
dynamic programming
*/