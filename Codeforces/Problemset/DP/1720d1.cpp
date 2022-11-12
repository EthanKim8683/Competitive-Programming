#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=3e5;
const I A=200;
const I LOGA=9;

I a_arr[N];
I dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(dp,n,1);
    for(I i=0;i<n;i++)for(I j=0;j<(1<<LOGA);j++){
      if(i-j<0)continue;
      I a=a_arr[i],b=a_arr[i-j];
      if((b^i)<(a^(i-j)))dp[i]=max(dp[i],dp[i-j]+1);
    }
    printf("%i\n",*max_element(dp,dp+n));
  }
}