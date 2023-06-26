#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=300;
const Lli MIN=-1e18;
I a_arr[N][N];
Lli dp[2][N][N][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0][0],&dp[0][0][0][0]+2*N*N*2,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>a_arr[i][j];
  dp[0][0][0][0]=dp[0][0][0][1]=a_arr[0][0];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++){
    if(j+1<=k)dp[i%2][j+1][k][0]=max(dp[i%2][j+1][k][0],dp[i%2][j][k][0]+(j+1<k)*a_arr[i][j+1]);
    if(j+1<=k)dp[i%2][j+1][k][1]=max(dp[i%2][j+1][k][1],dp[i%2][j][k][0]+(j+1<k)*a_arr[i][j+1]);
    if(k+1<n)dp[i%2][j][k+1][1]=max(dp[i%2][j][k+1][1],dp[i%2][j][k][0]+a_arr[i][k+1]);
    if(k+1<n)dp[i%2][j][k+1][1]=max(dp[i%2][j][k+1][1],dp[i%2][j][k][1]+a_arr[i][k+1]);
    if(j==k&&k+1<n)dp[i%2][j+1][k+1][1]=max(dp[i%2][j+1][k+1][1],dp[i%2][j][k][1]+a_arr[i][k+1]);
    if(j==k&&k+1<n)dp[i%2][j+1][k+1][1]=max(dp[i%2][j+1][k+1][1],dp[i%2][j][k][0]+a_arr[i][k+1]);
    if(i+1<n)dp[(i+1)%2][j][k][0]=max(dp[(i+1)%2][j][k][0],dp[i%2][j][k][0]+a_arr[i+1][j]+(k!=j)*a_arr[i+1][k]);
    if(i+1<n)dp[(i+1)%2][j][k][0]=max(dp[(i+1)%2][j][k][0],dp[i%2][j][k][1]+a_arr[i+1][j]+(k!=j)*a_arr[i+1][k]);
    if(i+1<n)dp[(i+1)%2][j][k][1]=max(dp[(i+1)%2][j][k][1],dp[i%2][j][k][0]+a_arr[i+1][j]+(k!=j)*a_arr[i+1][k]);
    if(i+1<n)dp[(i+1)%2][j][k][1]=max(dp[(i+1)%2][j][k][1],dp[i%2][j][k][1]+a_arr[i+1][j]+(k!=j)*a_arr[i+1][k]);
    if(i<n-1)dp[i%2][j][k][0]=dp[i%2][j][k][1]=MIN;
  }
  printf("%lli\n",max(dp[(n-1)%2][n-1][n-1][0],dp[(n-1)%2][n-1][n-1][1]));
}