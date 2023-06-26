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
    sort(a_arr,a_arr+n);
    I len=1;
    for(I i=1;i<n;i++){
      if(a_arr[i]!=a_arr[i-1])break;
      len++;
    }
    printf("%i\n",n-len);
  }
}