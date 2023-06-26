#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli k;cin>>n>>k,k--;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lli i=k/n,a=a_arr[i];
  I cur=upper_bound(a_arr,a_arr+n,a)-lower_bound(a_arr,a_arr+n,a);
  I pre=lower_bound(a_arr,a_arr+n,a)-a_arr;
  printf("%i %i\n",a_arr[i],a_arr[(k-(Lli)n*pre)/cur%n]);
}