#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;
Lli n,m;

B chk(Lli i){
  return i*(i-1)/2>=m;
}

Lli fnd(){
  Lli l=0,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  printf("%lli %lli\n",max(n-m*2,(Lli)0),n-fnd());
  return 0;
}