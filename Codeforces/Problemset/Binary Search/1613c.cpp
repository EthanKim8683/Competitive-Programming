#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=100;
const Lli H=1e18;

I a_arr[N];
I n;Lli h;

B chk(Lli x){
  Lli res=0;
  for(I i=0;i+1<n;i++){
    I a=a_arr[i],b=a_arr[i+1];
    res+=min((Lli)b-a,x);
  }
  res+=x;
  return res>=h;
}

Lli fnd(){
  Lli l=0,r=H;
  while(l<r){
    Lli m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>h;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    printf("%lli\n",fnd());
  }
}