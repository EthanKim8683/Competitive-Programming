#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I cnt=1;
    pair<I,I>res={3,-1};
    for(I i=1;i<n;i++){
      a_arr[i]==a_arr[i-1]?cnt++:cnt=1;
      res=max(res,{cnt,a_arr[i]});
    }
    auto[tot,a]=res;
    printf("%i\n",a);
  }
}