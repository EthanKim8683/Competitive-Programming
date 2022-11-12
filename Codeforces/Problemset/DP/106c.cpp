#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1000;

I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,c,d;cin>>n>>m>>c>>d;
  for(I i=0;i+c<=n;i++)dp[i+c]=max(dp[i+c],dp[i]+d);
  for(I i=0;i<m;i++){
    I a,b,c,d;cin>>a>>b>>c>>d;
    I x=a/b;
    for(I j=n;j>=0;j--)for(I k=0;k<=x&&j+k*c<=n;k++)dp[j+k*c]=max(dp[j+k*c],dp[j]+k*d);
  }
  printf("%i\n",*max_element(dp,dp+n+1));
}