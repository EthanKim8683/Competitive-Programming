#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

I n;
I t;

B chk(I x){
  return 5*x*(x+1)/2<=t;
}

I fnd(){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>k;
  t=240-k;
  printf("%i\n",fnd());
}