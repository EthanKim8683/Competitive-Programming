#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MAX=1e18;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli cur=accumulate(a_arr,a_arr+n,0ll),res=MAX;
    for(I i=0;i<n;i++)a_arr[n-1-i]-=i;
    sort(a_arr,a_arr+n);
    for(I i=1;i<=k;i++)cur-=a_arr[n-i],res=min(res,cur-(Lli)i*(i-1)/2);
    printf("%lli\n",res);
  }
}