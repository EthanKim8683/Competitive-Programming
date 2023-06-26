#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=300;
const I MAX=1e9;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I res=MAX;
    for(I i=1;i<n-1;i++)res=min(res,a_arr[i+1]-a_arr[i-1]);
    printf("%i\n",res);
  }
}