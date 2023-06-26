#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const Lli MOD=998244353;
Lli a_arr[N];
Lli b_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)a_arr[i]*=(Lli)(i+1)*(n-i);
  sort(a_arr,a_arr+n);
  sort(b_arr,b_arr+n);
  for(I i=0;i<n;i++)a_arr[i]%=MOD,b_arr[i]%=MOD;
  Lli res=0;
  for(I i=0;i<n;i++)(res+=a_arr[i]*b_arr[n-1-i])%=MOD;
  printf("%lli\n",res);
}