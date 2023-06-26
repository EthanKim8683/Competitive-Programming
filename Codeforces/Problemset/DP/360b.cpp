#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2000;
const I A=1e9;
const I MAX=1e9;
I a_arr[N];
I dp[N+1];
I n,k;
B chk(I x){
  fill_n(dp,n+1,MAX);
  dp[0]=0;
  for(I i=0;i<n;i++){
    dp[i]=min(dp[i],i);
    for(I j=0;i+j+1<n;j++)if((abs(a_arr[i]-a_arr[i+j+1])+j)/(j+1)<=x)dp[i+j+1]=min(dp[i+j+1],dp[i]+j);
    dp[n]=min(dp[n],dp[i]+n-1-i);
  }
  dp[n]=min(dp[n],n);
  return dp[n]<=k;
}
I fnd(){
  I l=0,r=2*A;
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  printf("%i\n",fnd());
}