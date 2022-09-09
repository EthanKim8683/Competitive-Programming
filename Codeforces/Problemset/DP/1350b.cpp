#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100000;

I s_arr[N+1];
I dp[N+1];

void cmb(I& a,I b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=1;i<=n;i++)cin>>s_arr[i];
    I res=0;
    fill_n(dp,n+1,1);
    for(I i=1;i<=n;i++){
      cmb(res,dp[i]);
      for(I j=2*i;j<=n;j+=i)if(s_arr[j]>s_arr[i])
        cmb(dp[j],dp[i]+1);
    }
    printf("%i\n",res);
  }
  return 0;
}