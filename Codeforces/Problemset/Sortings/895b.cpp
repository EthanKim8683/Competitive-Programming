#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,x,k;cin>>n>>x>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  Lli res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    Lli l=a/x*x-(Lli)k*x+1;
    Lli r=min(a/x*x-(Lli)k*x+x,(Lli)a);
    if(l>r)continue;
    res+=upper_bound(a_arr,a_arr+n,r)-lower_bound(a_arr,a_arr+n,l);
  }
  printf("%lli\n",res);
}