#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  printf("%i\n",*max_element(a_arr,a_arr+n)-*min_element(a_arr,a_arr+n)-n+1);
}