#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=25;
I a_arr[2*N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<2*n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+2*n);
    for(I i=0;i<n;i++)printf("%i %i ",a_arr[i],a_arr[i+n]);
    printf("\n");
  }
}