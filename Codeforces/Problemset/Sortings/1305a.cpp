#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
I b_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    sort(a_arr,a_arr+n);
    sort(b_arr,b_arr+n);
    for(I i=0;i<n;i++)printf("%i ",a_arr[i]);
    printf("\n");
    for(I i=0;i<n;i++)printf("%i ",b_arr[i]);
    printf("\n");
  }
}