#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1500;
const I M=1500;
const Lli MIN=-1e18;
I tabs[N][M];
Lli ps[N][M];
Lli dp[N][M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*M,MIN);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>tabs[i][j];
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)ps[i][j]=tabs[i][j];
    for(I j=0;j+1<m;j++)ps[i][j+1]+=ps[i][j];
  }
  copy_n(ps[0],m,dp[0]);
  for(I i=1;i<n;i++){
    if(i%2==0){
      for(I j=0+1;j<m;j++)dp[i][j]=dp[i-1][j-1];
      for(I j=0;j+1<m;j++)dp[i][j+1]=max(dp[i][j+1],dp[i][j]);
    }
    if(i%2==1){
      for(I j=0;j+1<m;j++)dp[i][j]=dp[i-1][j+1];
      for(I j=m-1;j>0;j--)dp[i][j-1]=max(dp[i][j-1],dp[i][j]);
    }
    for(I j=0;j<m;j++)dp[i][j]+=ps[i][j];
  }
  printf("%lli\n",*max_element(dp[n-1],dp[n-1]+m));
}