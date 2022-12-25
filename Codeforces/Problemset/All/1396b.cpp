#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I tot=accumulate(a_arr,a_arr+n,0);
    I upp=*max_element(a_arr,a_arr+n);
    printf("%s\n",upp*2>tot||tot%2?"T":"HL");
  }
}