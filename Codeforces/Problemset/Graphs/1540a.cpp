#include<iostream>
#include<cstdio>
#include<algorithm>
#include<numeric>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

I d_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>d_arr[i];
    sort(d_arr,d_arr+n);
    Lli res=*max_element(d_arr,d_arr+n);
    Lli tot=0;
    for(I i=0;i<n;i++)tot+=d_arr[i];
    for(I i=0;i+1<n;i++){
      res-=tot;
      tot-=(Lli)(d_arr[i+1]-d_arr[i])*(n-i-1);
    }
    printf("%lli\n",res);
  }
  return 0;
}