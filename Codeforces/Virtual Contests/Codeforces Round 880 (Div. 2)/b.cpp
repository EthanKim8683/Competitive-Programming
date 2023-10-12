#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
I n,k,g;
B chk(I x){
  if(g%2==0){
    I f=g/2-1;
    return 2*x+(2*x+f-1)/f<=n;
  }
  if(g%2==1){
    I f=g/2;
    return 2*x+(x+f-1)/f<=n;
  }
}
I fnd(){
  I l=0,r=k;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k>>g;
    printf("%lli\n",g==2?0:(Lli)fnd()*g);
  }
}