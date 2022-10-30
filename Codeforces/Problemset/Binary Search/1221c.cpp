#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

I c,m,x;

B chk(I i){
  return c-i+m-i+x>=i;
}

I fnd(){
  I l=0,r=min(c,m);
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    cin>>c>>m>>x;
    printf("%i\n",fnd());
  }
}