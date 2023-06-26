#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=1e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I j=max_element(a_arr,a_arr+n)-a_arr;
    Lf res=0;
    for(I i=0;i<n;i++)if(i!=j)res+=a_arr[i];
    res/=n-1,res+=a_arr[j];
    printf("%.9Lf\n",res);
  }
}