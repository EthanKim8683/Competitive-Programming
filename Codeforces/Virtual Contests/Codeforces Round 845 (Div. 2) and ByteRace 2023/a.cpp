#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I pre=a_arr[0]%2,cnt=1;
    for(I i=1;i<n;i++){
      I cur=a_arr[i]%2;
      if(cur!=pre)cnt++,pre=cur;
    }
    printf("%i\n",n-cnt);
  }
}