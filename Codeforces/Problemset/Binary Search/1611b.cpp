#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

I a,b;

I bld(I x){
  return max(min(a-3*x,b-1*x),min(b-3*x,a-1*x))/2+x;
}

B chk(I x){
  if(a>b)return a-3*x>=b-1*x;
  if(b>a)return b-3*x>=a-1*x;
  return 0;
}

I fnd(){
  I l=0,r=min(a,b);
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
    cin>>a>>b;
    printf("%i\n",bld(fnd()));
  }
}