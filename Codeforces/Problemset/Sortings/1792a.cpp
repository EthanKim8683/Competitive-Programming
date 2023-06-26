#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I h_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>h_arr[i];
    I cnt=0;
    for(I i=0;i<n;i++)cnt+=h_arr[i]==1;
    printf("%i\n",cnt/2+(n-cnt/2*2));
  }
}