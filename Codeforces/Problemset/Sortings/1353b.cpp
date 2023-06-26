#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=30;
I a_arr[N];
I b_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    sort(a_arr,a_arr+n);
    sort(b_arr,b_arr+n);
    for(I i=0;i<k;i++)if(a_arr[i]<b_arr[n-1-i])swap(a_arr[i],b_arr[n-1-i]);
    printf("%i\n",accumulate(a_arr,a_arr+n,0));
  }
}