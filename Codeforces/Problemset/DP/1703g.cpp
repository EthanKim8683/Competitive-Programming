#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I a_arr[N];
Lli dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    fill_n(dp,n,0);
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++){
      I a=a_arr[n-1-i];
      for(I j=0;a/=2;j++)if(i+j<n)dp[n-1-i-j]+=a;
    }
    Lli res=0,sum=0;
    for(I i=0;i<n;i++){
      res=max(res,dp[i]+sum);
      sum+=a_arr[i]-k;
    }
    res=max(res,sum);
    printf("%lli\n",res);
  }
}