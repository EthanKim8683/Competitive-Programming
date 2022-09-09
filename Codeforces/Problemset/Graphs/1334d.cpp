#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

Lli n;

Lli ind(Lli i){
  return (n-1+n-i)*i;
}

Lli fnd(Lli i){
  Lli l=0,r=n;
  while(l<r){
    Lli m=l+(r-l+1)/2;
    if(ind(m)<=i)l=m;
    else r=m-1;
  }
  return l;
}

Lli val(Lli i){
  if(i==n*(n-1))return 0;
  Lli f=fnd(i);
  return i%2?(i-ind(f)+1)/2+f:f;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli l,r;cin>>n>>l>>r,l--,r--;
    for(Lli i=l;i<=r;i++)printf("%lli ",val(i)+1);
    printf("\n");
  }
  return 0;
}