#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
Lli a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    for(I i=0;i<k&&n-2-i>=0;i++)a_arr[n-1]+=a_arr[n-2-i],a_arr[n-2-i]=0;
    printf("%lli\n",a_arr[n-1]-*min_element(a_arr,a_arr+n));
  }
}