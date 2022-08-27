#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
Lli dp[N];
I n;

Lli dfs(I i){
  if(i>=n)return 0;
  if(dp[i])return dp[i];
  I a=a_arr[i];
  return dp[i]=a+dfs(i+a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    fill_n(dp,n,0);
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli res=0;
    for(I i=0;i<n;i++)res=max(res,dfs(i));
    printf("%lli\n",res);
  }
  return 0;
}