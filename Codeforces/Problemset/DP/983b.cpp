#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=5000;

I a_arr[N];
I dp[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)dp[0][i]=a_arr[i];
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++)
    dp[i][j]=dp[i-1][j]^dp[i-1][j+1];
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++)
    dp[i][j]=max(dp[i][j],max(dp[i-1][j],dp[i-1][j+1]));
  I q;cin>>q;
  while(q--){
    I l,r;cin>>l>>r;
    printf("%i\n",dp[r-l][l-1]);
  }
}