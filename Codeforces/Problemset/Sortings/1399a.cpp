#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    B res=1;
    for(I i=0;i+1<n;i++)res&=a_arr[i+1]-a_arr[i]<=1;
    printf("%s\n",res?"YES":"NO");
  }
}