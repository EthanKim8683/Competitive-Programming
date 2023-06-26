#include<bits/stdc++.h>
using namespace std;
using I=int;
I b_arr[7];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    for(I i=0;i<7;i++)cin>>b_arr[i];
    printf("%i %i %i\n",b_arr[0],b_arr[1],b_arr[6]-b_arr[0]-b_arr[1]);
  }
}