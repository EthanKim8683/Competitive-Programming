#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I h_arr[2][N];
Lli dp[N+1][2];

void cmb(Lli&a,Lli b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[0][i];
  for(I i=0;i<n;i++)cin>>h_arr[1][i];
  for(I i=0;i<n;i++){
    cmb(dp[i+1][0],dp[i][0]);
    cmb(dp[i+1][1],dp[i][1]);
    cmb(dp[i+1][1],dp[i][0]+h_arr[1][i]);
    cmb(dp[i+1][0],dp[i][1]+h_arr[0][i]);
  }
  printf("%lli\n",max(dp[n][0],dp[n][1]));
  return 0;
}