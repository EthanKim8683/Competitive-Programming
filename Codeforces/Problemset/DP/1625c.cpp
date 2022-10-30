#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=500;
const I K=N-1;
const I MAX=1e9;

I d_arr[N+1];
I a_arr[N+1];
I dp[N+1][K+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(K+1),MAX);
  I n,l,k;cin>>n>>l>>k;
  for(I i=0;i<n;i++)cin>>d_arr[i];
  for(I i=0;i<n;i++)cin>>a_arr[i];
  d_arr[n]=l;
  dp[0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++)for(I l=0;i+l+1<=n&&j+l<=k;l++)
    dp[i+l+1][j+l]=min(dp[i+l+1][j+l],dp[i][j]+(d_arr[i+l+1]-d_arr[i])*a_arr[i]);
  printf("%i\n",*min_element(dp[n],dp[n]+k+1));
}