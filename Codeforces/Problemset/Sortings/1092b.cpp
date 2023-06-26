#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  I res=0;
  for(I i=0;i<n;i+=2)res+=a_arr[i+1]-a_arr[i];
  printf("%i\n",res);
}