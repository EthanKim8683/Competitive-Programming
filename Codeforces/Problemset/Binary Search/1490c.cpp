#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I A=1e4;

Lli cub(Lli x){
  return x*x*x;
}

Lli fnd(Lli x){
  Lli l=0,r=A;
  while(l<r){
    Lli m=l+(r-l+1)/2;
    if(cub(m)<=x)l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli x;cin>>x;
    Lli rgt=fnd(x);
    B res=0;
    for(Lli i=1;i<=rgt&&!res;i++){
      Lli j=fnd(x-cub(i));
      res|=j>0&&cub(i)+cub(j)==x;
    }
    printf("%s\n",res?"YES":"NO");
  }
}