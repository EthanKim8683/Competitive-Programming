#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

I a,b;

I bld(I x){
  I bth=max(min(a-x*2,b-x*1),min(b-x*2,a-x*1));
  if(bth<0)return 0;
  return x+bth/3*2;
}

B chk(I x){
  if(a>b)return a-x*2>=b-x*1;
  if(b>a)return b-x*2>=a-x*1;
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
    I x=fnd();
    printf("%i\n",max(bld(x),bld(x+1)));
  }
}