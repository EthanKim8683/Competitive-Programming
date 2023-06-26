#include<bits/stdc++.h>
using namespace std;
using I=int;
I nums[3];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    for(I i=0;i<3;i++)cin>>nums[i];
    nth_element(nums,nums+1,nums+3);
    printf("%i\n",nums[1]);
  }
}