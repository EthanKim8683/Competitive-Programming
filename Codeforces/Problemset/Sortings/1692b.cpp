#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=50;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I len=1,tot=0;
    for(I i=1;i<n;i++)a_arr[i]==a_arr[i-1]?len++:(tot+=len-1,len=1);
    tot=(tot+len)/2*2;
    printf("%i\n",n-tot);
  }
}