#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=2e5;
const I MIN=-2e9;

I a_arr[N];
I dp[N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)dp[i][0]=dp[i][1]=MIN;
    dp[0][s[0]-'0']=0;
    for(I i=0;i+1<n;i++){
      I a=a_arr[i];
      if(s[i+1]=='1'){
        dp[i+1][0]=max(dp[i+1][0],dp[i][0]+a);
        dp[i+1][1]=max(dp[i+1][1],dp[i][0]);
        dp[i+1][1]=max(dp[i+1][1],dp[i][1]+a);
      }else{
        dp[i+1][0]=max(dp[i+1][0],dp[i][0]);
        dp[i+1][0]=max(dp[i+1][0],dp[i][1]+a);
      }
    }
    dp[n-1][1]+=a_arr[n-1];
    printf("%i\n",max(dp[n-1][0],dp[n-1][1]));
  }
}