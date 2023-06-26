#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MAX=1e9;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)a_arr[i]=__builtin_ctz(a_arr[i]);
    sort(a_arr,a_arr+n);
    I len=1;
    for(I i=1;i<n&&a_arr[i]==a_arr[i-1];i++)len++;
    printf("%i\n",a_arr[0]?a_arr[0]+n-1:n-len);
  }
}