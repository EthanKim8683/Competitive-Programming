#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I K=1000;
const I MAX=1e9;

I a_arr[K];
I n,s,k;

B chk1(I x){
  auto low=lower_bound(a_arr,a_arr+k,s);
  auto upp=upper_bound(a_arr,a_arr+k,x);
  return (x-s+1)-(upp-low)>=1;
}

B chk2(I x){
  auto low=lower_bound(a_arr,a_arr+k,x);
  auto upp=upper_bound(a_arr,a_arr+k,s);
  return (s-x+1)-(upp-low)>=1;
}

I fnd1(){
  I l=s,r=n+1;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk1(m))r=m;
    else l=m+1;
  }
  if(l==n+1)return MAX;
  return l-s;
}

I fnd2(){
  I l=0,r=s;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk2(m))l=m;
    else r=m-1;
  }
  if(l==0)return MAX;
  return s-l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>s>>k;
    for(I i=0;i<k;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+k);
    printf("%i\n",min(fnd1(),fnd2()));
  }
}