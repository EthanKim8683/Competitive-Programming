#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I res=0;
    for(I i=0;i<n-2*k;i++)res+=a_arr[i];
    for(I i=0;i<k;i++)res+=a_arr[n-2*k+i]/a_arr[n-2*k+i+k];
    printf("%i\n",res);
  }
}