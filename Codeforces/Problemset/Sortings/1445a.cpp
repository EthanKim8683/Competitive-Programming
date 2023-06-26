#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50;
I a_arr[N];
I b_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x;cin>>n>>x;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    reverse(b_arr,b_arr+n);
    B res=1;
    for(I i=0;i<n;i++)res&=a_arr[i]+b_arr[i]<=x;
    printf("%s\n",res?"Yes":"No");
  }
}