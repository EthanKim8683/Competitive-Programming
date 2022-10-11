#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MIN=-9e18;

I a_arr[N];
Lli dp[3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p,q,r;cin>>n>>p>>q>>r;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(dp,3,MIN);
  for(I i=0;i<n;i++){
    Lli a=a_arr[i];
    dp[0]=max(dp[0],p*a);
    dp[1]=max(dp[1],dp[0]+q*a);
    dp[2]=max(dp[2],dp[1]+r*a);
  }
  printf("%lli\n",dp[2]);
}