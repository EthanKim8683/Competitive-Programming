#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I A=1e9;
const Lli MAX=1e18;
pair<I,I>slcs[N];
I n;
Lli wid(I h){
  Lli res=0;
  for(I i=0;i<n;i++){
    auto[b,a]=slcs[i];
    if(b>h)swap(a,b);
    if(b>h)return MAX;
    res+=a;
  }
  return res;
}
I hgt(I h){
  I res=0;
  for(I i=0;i<n;i++){
    auto[b,a]=slcs[i];
    if(b>h)swap(a,b);
    res=max(res,b);
  }
  return res;
}
I fnd1(){
  I l=0,r=A;
  while(l<r){
    I m=l+(r-l+1)/2;
    wid(m)>=hgt(m)?l=m:r=m-1;
  }
  return l;
}
I fnd2(){
  I l=0,r=A;
  while(l<r){
    I m=l+(r-l)/2;
    wid(m)<=hgt(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++){
      I a,b;cin>>a>>b;
      if(a>b)swap(a,b);
      slcs[i]={b,a};
    }
    Lli h1=hgt(fnd1()),w1=wid(h1);
    Lli h2=hgt(fnd2()),w2=wid(h2);
    printf("%lli\n",2*min(w1+h1,w2+h2));
  }
}