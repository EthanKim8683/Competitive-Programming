#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
I a_arr[N];
I b_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)cin>>b_arr[i];
    for(I i=0;i<n;i++)if(a_arr[i]>b_arr[i])swap(a_arr[i],b_arr[i]);
    printf("%s\n",*max_element(a_arr,a_arr+n)==a_arr[n-1]&&*max_element(b_arr,b_arr+n)==b_arr[n-1]?"Yes":"No");
  }
}