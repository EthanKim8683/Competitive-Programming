#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  nth_element(a_arr,a_arr+n/2,a_arr+n);
  printf("%i\n",a_arr[n/2]);
}