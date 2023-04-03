#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
map<I,I>viss;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    viss.clear();
    I dif=*max_element(a_arr,a_arr+n)-*min_element(a_arr,a_arr+n);
    Lli res=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      res+=viss[a-dif];
      if(dif>0)res+=viss[a+dif];
      viss[a]++;
    }
    printf("%lli\n",2*res);
  }
}