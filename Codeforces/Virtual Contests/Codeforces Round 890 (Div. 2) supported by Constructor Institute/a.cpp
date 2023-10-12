#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=50;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I res=0;
    for(I i=0;i+1<n;i++)if(a_arr[i+1]<a_arr[i])res=max(res,a_arr[i]);
    printf("%i\n",res);
  }
}