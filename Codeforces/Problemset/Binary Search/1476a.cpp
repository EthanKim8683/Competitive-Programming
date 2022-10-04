#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I K=1e9;

I n,k;

B chk1(I x,I y){
  return (Lli)k*y-x>=n-1;
}

I fnd1(I x){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk1(x,m))r=m;
    else l=m+1;
  }
  return l;
}

B chk2(I x){
  return (Lli)k*fnd1(x)<=(Lli)x*n;
}

I fnd2(){
  I l=1,r=K;
  while(l<r){
    I m=l+(r-l)/2;
    if(chk2(m))r=m;
    else l=m+1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k;
    printf("%i\n",fnd2());
  }
}