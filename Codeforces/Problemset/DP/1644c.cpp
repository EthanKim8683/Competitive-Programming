#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=5000;
const I MIN=-1e9;

I a_arr[N];
Lli ps[N+1];
Lli dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x;cin>>n>>x;
    fill_n(dp,n+1,MIN);
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    for(I i=1;i<=n;i++)for(I j=0;j+i<=n;j++)dp[i]=max(dp[i],ps[j+i]-ps[j]);
    for(I i=n;i-1>=0;i--)dp[i-1]=max(dp[i-1],dp[i]);
    for(I i=0;i<=n;i++)dp[i]+=(Lli)i*x;
    for(I i=0;i+1<=n;i++)dp[i+1]=max(dp[i+1],dp[i]);
    for(I i=0;i<=n;i++)printf("%lli ",max(dp[i],(Lli)0));
    printf("\n");
  }
}