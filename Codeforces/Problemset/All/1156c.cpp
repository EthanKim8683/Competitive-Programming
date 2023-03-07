#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I x_arr[N];
multiset<I>unvs;
I n,z;
B chk(I m){
  unvs.clear();
  for(I i=m;i<n;i++)unvs.insert(x_arr[i]);
  for(I i=0;i<m;i++){
    auto it=unvs.lower_bound(x_arr[i]+z);
    if(it==unvs.end())return 0;
    unvs.erase(it);
  }
  return 1;
}
I fnd(){
  I l=0,r=n/2;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>z;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  sort(x_arr,x_arr+n);
  printf("%i\n",fnd());
}