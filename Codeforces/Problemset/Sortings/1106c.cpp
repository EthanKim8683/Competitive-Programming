#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lli res=0;
  for(I i=0;i<n/2;i++){
    Lli sum=a_arr[i]+a_arr[n-i-1];
    res+=sum*sum;
  }
  printf("%lli\n",res);
}