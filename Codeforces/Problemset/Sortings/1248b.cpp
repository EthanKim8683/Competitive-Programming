#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lli wid=0,hgt=0;
  I i=0;
  for(;i<n/2;i++)wid+=a_arr[i];
  for(;i<n;i++)hgt+=a_arr[i];
  printf("%lli\n",wid*wid+hgt*hgt);
}