#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
I h_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,a,b;cin>>n>>a>>b;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  sort(h_arr,h_arr+n);
  printf("%i\n",h_arr[b]-h_arr[b-1]);
}