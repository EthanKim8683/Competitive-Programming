#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1e9;

I n;

B chk(Lli x){
  return x*x>=n;
}

I fnd(){
  I l=0,r=N;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  I x=fnd();
  I y=n/x+!!(n%x);
  printf("%i\n",x+y);
}