#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,d;cin>>n>>d;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I low=a_arr[0]+a_arr[1];
    B res=1;
    for(I i=0;i<n;i++)res&=min(a_arr[i],low)<=d;
    printf("%s\n",res?"YES":"NO");
  }
}