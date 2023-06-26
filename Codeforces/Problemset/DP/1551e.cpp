#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
const I MAX=1e9;
const I MIN=-1e9;
I a_arr[N];
I dp[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(dp,n,MIN);
    I res=MAX;
    for(I i=0;i<n;i++){
      if(i>=a_arr[i]-1)dp[i]=max(dp[i],1);
      for(I j=0;j<i;j++){
        I a=a_arr[i],b=a_arr[j];
        if(i-j>=a-b&&a>b)dp[i]=max(dp[i],dp[j]+1);
      }
      if(dp[i]>=k)res=min(res,i-a_arr[i]+1);
    }
    printf("%i\n",res==MAX?-1:res);
  }
}