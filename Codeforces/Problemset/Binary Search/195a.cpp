#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

I a,b,c,d,e;

B chk(I x){
  return x*b+(e-x)*(b-a)>=0;
}

I fnd(){
  I l=0,r=e;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>a>>b>>c;
  d=a*c;
  e=d/b+!!(d%b);
  printf("%i\n",fnd());
}