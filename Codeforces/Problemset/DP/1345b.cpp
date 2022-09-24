#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;
using B=bool;

const I N=1e9;

I n;

Lli cnt(Lli x){
  return x*(x-1)/2+x*(x+1)/2*2;
}

B chk(Lli x){
  return cnt(x)<=n;
}

I fnd(){
  I l=0,r=N;
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
    cin>>n;
    I res=0;
    while(1){
      I x=fnd();
      if(!x)break;
      res++;
      n-=cnt(x);
    }
    printf("%i\n",res);
  }
}