#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=5000;

I s_arr[N];
Lli dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>s_arr[i];
    fill_n(dp,n,0);
    Lli res=0;
    for(I i=0;i<n;i++){
      Lli a=s_arr[i],b=dp[i];
      while(b>0&&a>1){
        if(i+a<n)dp[i+a]++;
        a--,b--;
      }
      if(i+a<n)dp[i+a]+=b;
      for(I j=2;j<=a&&i+j<n;j++)dp[i+j]++;
      res+=a-1;
    }
    printf("%lli\n",res);
  }
}