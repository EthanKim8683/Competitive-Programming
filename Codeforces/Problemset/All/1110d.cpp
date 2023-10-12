#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e6;
const I M=1e6;
const I MIN=-1e9;
I a_arr[N];
I cnts[M];
I dp[M][6+1][6+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+M*(6+1)*(6+1),MIN);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts[a_arr[i]-1]++;
  if(m<3){
    I res=0;
    for(I i=0;i<m;i++)res+=cnts[i]/3;
    printf("%i\n",res),exit(0);
  }
  dp[0][min(cnts[0],6)][min(cnts[1],6)]=0;
  for(I i=0;i+2<m;i++){
    I cnt=min(cnts[i+2],6);
    for(I j=0;j<=6;j++)for(I k=0;k<=6;k++)for(I l=0;l<=min(min(j,k),cnt);l++)dp[i+1][k-l][cnt-l]=max(dp[i+1][k-l][cnt-l],dp[i][j][k]+l+(cnts[i]-min(cnts[i],6)+j-l)/3);
  }
  I res=MIN;
  for(I i=0;i<=6;i++)for(I j=0;j<=6;j++)res=max(res,dp[m-2][i][j]+(cnts[m-2]-min(cnts[m-2],6)+i)/3+(cnts[m-1]-min(cnts[m-1],6)+j)/3);
  printf("%i\n",res);
}