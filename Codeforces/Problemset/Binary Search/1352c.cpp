#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

I n,k;

Lli bld(Lli x){
  return x*n+k-x*(n-1);
}

B chk(Lli x){
  return x*(n-1)<k;
}

I fnd(){
  I l=0,r=k;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k;
    printf("%lli\n",bld(fnd()));
  }
}