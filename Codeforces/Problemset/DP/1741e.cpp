#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I b_arr[N];
B dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>b_arr[i];
    fill_n(dp,n+1,0);
    dp[0]=1;
    for(I i=0;i<n;i++){
      I b=b_arr[i];
      if(i-b>=0)dp[i+1]|=dp[i-b];
      if(i+b<=n)dp[i+b+1]|=dp[i];
    }
    printf("%s\n",dp[n]?"YES":"NO");
  }
}