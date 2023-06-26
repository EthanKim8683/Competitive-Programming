#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I low=*min_element(a_arr,a_arr+n);
    Lli res=0;
    for(I i=0;i<n;i++)res+=a_arr[i]-low;
    printf("%lli\n",res);
  }
}