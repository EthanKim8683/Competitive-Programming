#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I K=N/2;
const I MAX=1e9;
I a_arr[N];
I vals[N][3],csts[N][3];
I dp[N+1][K+1][4];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(K+1)*4,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    vals[i][0]=vals[i][1]=vals[i][2]=a_arr[i];
    if(i-1>=0)vals[i][0]=min(a_arr[i-1]-1,a_arr[i]),csts[i][0]=a_arr[i]-vals[i][0];
    if(i+1<n)vals[i][1]=min(a_arr[i+1]-1,a_arr[i]),csts[i][1]=a_arr[i]-vals[i][1];
  }
  I k=(n+1)/2;
  dp[1][1][3]=0;
  for(I i=0;i<3;i++)dp[1][0][i]=csts[0][i];
  for(I i=1;i<n;i++)for(I j=0;j<=k;j++){
    if(vals[i][2]>vals[i-1][0]&&j+1<=k)dp[i+1][j+1][3]=min(dp[i+1][j+1][3],dp[i][j][0]);
    if(vals[i][2]>vals[i-1][1]&&j+1<=k)dp[i+1][j+1][3]=min(dp[i+1][j+1][3],dp[i][j][1]);
    if(vals[i][2]>vals[i-1][2]&&j+1<=k)dp[i+1][j+1][3]=min(dp[i+1][j+1][3],dp[i][j][2]);
    if(vals[i-1][2]>vals[i][0])dp[i+1][j][0]=min(dp[i+1][j][0],dp[i][j][3]+csts[i][0]);
    if(vals[i-1][2]>vals[i][1])dp[i+1][j][1]=min(dp[i+1][j][1],dp[i][j][3]+csts[i][1]);
    if(vals[i-1][2]>vals[i][2])dp[i+1][j][2]=min(dp[i+1][j][2],dp[i][j][3]+csts[i][2]);
    I low=*min_element(dp[i][j],dp[i][j]+3);
    for(I l=0;l<3;l++)dp[i+1][j][l]=min(dp[i+1][j][l],low+csts[i][l]);
  }
  for(I i=1;i<=k;i++)printf("%i ",*min_element(dp[n][i],dp[n][i]+4));
}