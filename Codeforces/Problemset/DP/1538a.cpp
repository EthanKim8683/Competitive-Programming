#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;
const I MAX=1e9;

I a_arr[N];

I main(){
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I a=min_element(a_arr,a_arr+n)-a_arr;
    I b=max_element(a_arr,a_arr+n)-a_arr;
    I res=MAX;
    res=min(res,max(a+1,b+1));
    res=min(res,max(n-a,n-b));
    res=min(res,(a+1)+(n-b));
    res=min(res,(n-a)+(b+1));
    printf("%i\n",res);
  }
}