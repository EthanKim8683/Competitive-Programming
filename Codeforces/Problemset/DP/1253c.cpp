#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=200000;
const I M=N;

I a_arr[N];
Lli dp[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lli res=0;
  for(I i=0;i<n;i++)printf("%lli ",res+=(dp[i%m]+=a_arr[i]));
}