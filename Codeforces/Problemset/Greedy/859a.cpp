#include<bits/stdc++.h>

using namespace std;

using I=int;

const I K=25;

I r_arr[K];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  for(I i=0;i<k;i++)cin>>r_arr[i];
  printf("%i\n",max(0,*max_element(r_arr,r_arr+k)-25));
}