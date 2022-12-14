#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I a_arr[N];
map<I,I>vals;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    vals.clear();
    for(I i=0;i<n;i++)vals[a_arr[i]]++;
    Lli res=n/2,rem=n;
    for(auto[val,cnt]:vals){
      rem-=cnt;
      res=max(res,rem*(n-rem));
    }
    printf("%lli\n",res);
  }
}