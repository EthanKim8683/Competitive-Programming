#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e5;

I a_arr[N];
I h;
I a,b;

B chk(I x){
  return (Lli)(x-x/2)*a+(Lli)(x/2)*b>=h;
}

I fnd(){
  I l=0,r=h;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>h;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n,greater<I>());
    a=a_arr[0],b=a_arr[1];
    printf("%i\n",fnd());
  }
}