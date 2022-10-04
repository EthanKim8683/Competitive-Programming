#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I X=63244;

I n;

B chk(Lli x){
  Lli a=x/2,b=x-x/2;
  return (1+a)*(1+b)>=n;
}

I fnd(){
  I l=0,r=X;
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
    cin>>n;
    printf("%i\n",fnd());
  }
}