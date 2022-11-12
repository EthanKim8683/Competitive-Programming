#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I m_arr[N];
I dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>m_arr[i];
  for(I i=0;i<n;i++)dp[i]=m_arr[i]+1;
  for(I i=n-1;i-1>=0;i--)dp[i-1]=max(dp[i-1],dp[i]-1);
  for(I i=0;i+1<n;i++)dp[i+1]=max(dp[i+1],dp[i]);
  Lli res=0;
  for(I i=0;i<n;i++)res+=dp[i]-m_arr[i]-1;
  printf("%lli\n",res);
}