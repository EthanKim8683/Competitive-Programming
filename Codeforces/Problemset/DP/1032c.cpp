#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I a_arr[N];
I dp[N][5];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*5,-1);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(dp[0],5,0);
  for(I i=0;i+1<n;i++)for(I j=0;j<5;j++){
    if(dp[i][j]==-1)continue;
    I a=a_arr[i],b=a_arr[i+1];
    if(b>a)for(I k=j+1;k<5;k++)dp[i+1][k]=j;
    if(b<a)for(I k=0;k<j;k++)dp[i+1][k]=j;
    if(b==a)for(I k=0;k<5;k++)if(j!=k)dp[i+1][k]=j;
  }
  I j=max_element(dp[n-1],dp[n-1]+5)-dp[n-1];
  if(dp[n-1][j]==-1)printf("-1\n"),exit(0);
  for(I i=n-1;i>=0;i--)ress[i]=j,j=dp[i][j];
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
}