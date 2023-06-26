#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I M=100;
I a_arr[N];
I b_arr[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I m;cin>>m;
  for(I i=0;i<m;i++)cin>>b_arr[i];
  printf("%i %i\n",*max_element(a_arr,a_arr+n),*max_element(b_arr,b_arr+m));
}