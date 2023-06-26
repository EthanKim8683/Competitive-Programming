#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=50;
const I MAX=1e9;
I s_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>s_arr[i];
    sort(s_arr,s_arr+n);
    I res=MAX;
    for(I i=0;i+1<n;i++)res=min(res,s_arr[i+1]-s_arr[i]);
    printf("%i\n",res);
  }
}