#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=8;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I rem=10-n;
    printf("%i\n",rem*(rem-1)/2*6);
  }
}