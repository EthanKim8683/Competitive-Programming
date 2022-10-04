#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I S=1e9;

I n,s;

B chk(I x){
  return (Lli)(n-n/2-n%2+1)*x<=s;
}

I fnd(){
  I l=0,r=S;
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
    cin>>n>>s;
    printf("%i\n",fnd());
  }
}