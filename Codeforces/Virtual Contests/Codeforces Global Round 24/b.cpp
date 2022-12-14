#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I g=0;
    for(I i=0;i<n;i++)g=gcd(g,a_arr[i]);
    I m=*max_element(a_arr,a_arr+n);
    printf("%i\n",m/g);
  }
}