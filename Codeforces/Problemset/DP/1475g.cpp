#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I A=2e5;
I a_arr[N];
I viss[A+1];
I dp[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    fill_n(viss,A+1,0),fill_n(dp,A+1,0);
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)viss[a_arr[i]]++;
    for(I i=0;i<=A;i++)dp[i]=viss[i];
    for(I i=1;i<=A;i++)for(I j=2*i;j<=A;j+=i)dp[j]=max(dp[j],dp[i]+viss[j]);
    printf("%i\n",n-*max_element(dp,dp+A+1));
  }
}